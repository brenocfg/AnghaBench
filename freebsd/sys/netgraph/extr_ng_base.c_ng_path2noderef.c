#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * node_p ;
typedef  int /*<<< orphan*/ * hook_p ;
typedef  int /*<<< orphan*/  fullpath ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENXIO ; 
 scalar_t__ NG_HOOK_NOT_VALID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NG_HOOK_PEER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_HOOK_REF (int /*<<< orphan*/ *) ; 
 scalar_t__ NG_NODE_NOT_VALID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_REF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_UNREF (int /*<<< orphan*/ *) ; 
 int NG_PATHSIZ ; 
 int /*<<< orphan*/ * NG_PEER_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TOPOLOGY_WLOCK () ; 
 int /*<<< orphan*/  TOPOLOGY_WUNLOCK () ; 
 int /*<<< orphan*/  TRAP_ERROR () ; 
 int /*<<< orphan*/ * ng_findhook (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ng_name2noderef (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ng_path_parse (char*,char**,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

int
ng_path2noderef(node_p here, const char *address, node_p *destp,
    hook_p *lasthook)
{
	char    fullpath[NG_PATHSIZ];
	char   *nodename, *path;
	node_p  node, oldnode;

	/* Initialize */
	if (destp == NULL) {
		TRAP_ERROR();
		return EINVAL;
	}
	*destp = NULL;

	/* Make a writable copy of address for ng_path_parse() */
	strncpy(fullpath, address, sizeof(fullpath) - 1);
	fullpath[sizeof(fullpath) - 1] = '\0';

	/* Parse out node and sequence of hooks */
	if (ng_path_parse(fullpath, &nodename, &path, NULL) < 0) {
		TRAP_ERROR();
		return EINVAL;
	}

	/*
	 * For an absolute address, jump to the starting node.
	 * Note that this holds a reference on the node for us.
	 * Don't forget to drop the reference if we don't need it.
	 */
	if (nodename) {
		node = ng_name2noderef(here, nodename);
		if (node == NULL) {
			TRAP_ERROR();
			return (ENOENT);
		}
	} else {
		if (here == NULL) {
			TRAP_ERROR();
			return (EINVAL);
		}
		node = here;
		NG_NODE_REF(node);
	}

	if (path == NULL) {
		if (lasthook != NULL)
			*lasthook = NULL;
		*destp = node;
		return (0);
	}

	/*
	 * Now follow the sequence of hooks
	 *
	 * XXXGL: The path may demolish as we go the sequence, but if
	 * we hold the topology mutex at critical places, then, I hope,
	 * we would always have valid pointers in hand, although the
	 * path behind us may no longer exist.
	 */
	for (;;) {
		hook_p hook;
		char *segment;

		/*
		 * Break out the next path segment. Replace the dot we just
		 * found with a NUL; "path" points to the next segment (or the
		 * NUL at the end).
		 */
		for (segment = path; *path != '\0'; path++) {
			if (*path == '.') {
				*path++ = '\0';
				break;
			}
		}

		/* We have a segment, so look for a hook by that name */
		hook = ng_findhook(node, segment);

		TOPOLOGY_WLOCK();
		/* Can't get there from here... */
		if (hook == NULL || NG_HOOK_PEER(hook) == NULL ||
		    NG_HOOK_NOT_VALID(hook) ||
		    NG_HOOK_NOT_VALID(NG_HOOK_PEER(hook))) {
			TRAP_ERROR();
			NG_NODE_UNREF(node);
			TOPOLOGY_WUNLOCK();
			return (ENOENT);
		}

		/*
		 * Hop on over to the next node
		 * XXX
		 * Big race conditions here as hooks and nodes go away
		 * *** Idea.. store an ng_ID_t in each hook and use that
		 * instead of the direct hook in this crawl?
		 */
		oldnode = node;
		if ((node = NG_PEER_NODE(hook)))
			NG_NODE_REF(node);	/* XXX RACE */
		NG_NODE_UNREF(oldnode);	/* XXX another race */
		if (NG_NODE_NOT_VALID(node)) {
			NG_NODE_UNREF(node);	/* XXX more races */
			TOPOLOGY_WUNLOCK();
			TRAP_ERROR();
			return (ENXIO);
		}

		if (*path == '\0') {
			if (lasthook != NULL) {
				if (hook != NULL) {
					*lasthook = NG_HOOK_PEER(hook);
					NG_HOOK_REF(*lasthook);
				} else
					*lasthook = NULL;
			}
			TOPOLOGY_WUNLOCK();
			*destp = node;
			return (0);
		}
		TOPOLOGY_WUNLOCK();
	}
}