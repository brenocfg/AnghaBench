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
typedef  size_t u_int ;
struct nodeinfo {size_t hooks; } ;
struct ng_mesg {scalar_t__ data; } ;
struct namelist {size_t numnames; struct linkinfo* nodeinfo; } ;
struct linkinfo {scalar_t__ id; size_t* ourhook; } ;
struct hooklist {struct linkinfo* link; struct nodeinfo nodeinfo; } ;
struct asn_oid {size_t len; scalar_t__* subs; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGM_GENERIC_COOKIE ; 
 int /*<<< orphan*/  NGM_LISTHOOKS ; 
 int /*<<< orphan*/  NGM_LISTNODES ; 
 int /*<<< orphan*/  free (struct ng_mesg*) ; 
 int /*<<< orphan*/  hook_cmp ; 
 scalar_t__ index_compare (struct asn_oid const*,size_t,struct asn_oid*) ; 
 int /*<<< orphan*/  ncmp ; 
 struct ng_mesg* ng_dialog_id (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort (struct linkinfo*,size_t,int,int /*<<< orphan*/ ) ; 
 scalar_t__ snmp_node ; 
 size_t strlen (size_t*) ; 

__attribute__((used)) static int
find_hook_next(const struct asn_oid *oid, u_int sub, struct nodeinfo *nodeinfo,
    struct linkinfo *linkinfo)
{
	u_int idxlen = oid->len - sub;
	struct namelist *list;
	struct ng_mesg *resp;
	struct hooklist *hooks;
	struct ng_mesg *resp1;
	u_int node_index;
	struct asn_oid idx;
	u_int i, j;

	/*
	 * Get and sort Node list
	 */
	if ((resp = ng_dialog_id(snmp_node, NGM_GENERIC_COOKIE, NGM_LISTNODES,
	    NULL, 0)) == NULL)
		return (-1);
	list = (struct namelist *)(void *)resp->data;

	qsort(list->nodeinfo, list->numnames, sizeof(list->nodeinfo[0]), ncmp);

	/*
	 * If we have no index, take the first node and return the
	 * first hook.
	 */
	if (idxlen == 0) {
		node_index = 0;
		goto return_first_hook;
	}

	/*
	 * Locate node
	 */
	for (node_index = 0; node_index < list->numnames; node_index++)
		if (list->nodeinfo[node_index].id >= oid->subs[sub])
			break;

	/*
	 * If we have only the node part of the index take, or
	 * there is no node with that Id, take the first hook of that node.
	 */
	if (idxlen == 1 || node_index >= list->numnames ||
	    list->nodeinfo[node_index].id > oid->subs[sub])
		goto return_first_hook;

	/*
	 * We had an exact match on the node id and have (at last part)
	 * of the hook name index. Loop through the hooks of the node
	 * and find the next one.
	 */
	if ((resp1 = ng_dialog_id(list->nodeinfo[node_index].id,
	    NGM_GENERIC_COOKIE, NGM_LISTHOOKS, NULL, 0)) == NULL) {
		free(resp);
		return (-1);
	}
	hooks = (struct hooklist *)(void *)resp1->data;
	if (hooks->nodeinfo.hooks > 0) {
		qsort(hooks->link, hooks->nodeinfo.hooks,
		    sizeof(hooks->link[0]), hook_cmp);
		for (i = 0; i < hooks->nodeinfo.hooks; i++) {
			idx.len = strlen(hooks->link[i].ourhook) + 1;
			idx.subs[0] = idx.len - 1;
			for (j = 0; j < idx.len; j++)
				idx.subs[j + 1] = hooks->link[i].ourhook[j];
			if (index_compare(oid, sub + 1, &idx) < 0)
				break;
		}
		if (i < hooks->nodeinfo.hooks) {
			*nodeinfo = hooks->nodeinfo;
			*linkinfo = hooks->link[i];

			free(resp);
			free(resp1);
			return (0);
		}
	}

	/* no hook found larger than the index on the index node - take
	 * first hook of next node */
	free(resp1);
	node_index++;

  return_first_hook:
	while (node_index < list->numnames) {
		if ((resp1 = ng_dialog_id(list->nodeinfo[node_index].id,
		    NGM_GENERIC_COOKIE, NGM_LISTHOOKS, NULL, 0)) == NULL)
			break;
		hooks = (struct hooklist *)(void *)resp1->data;
		if (hooks->nodeinfo.hooks > 0) {
			qsort(hooks->link, hooks->nodeinfo.hooks,
			    sizeof(hooks->link[0]), hook_cmp);

			*nodeinfo = hooks->nodeinfo;
			*linkinfo = hooks->link[0];

			free(resp);
			free(resp1);
			return (0);
		}

		/* if we don't have hooks, try next node */
		free(resp1);
		node_index++;
	}

	free(resp);
	return (-1);
}