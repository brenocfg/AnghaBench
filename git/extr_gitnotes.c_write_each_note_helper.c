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
struct tree_write_stack {int /*<<< orphan*/  buf; struct tree_write_stack* next; } ;
struct object_id {int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ matches_tree_write_stack (struct tree_write_stack*,char const*) ; 
 int /*<<< orphan*/ * memchr (char const*,char,size_t) ; 
 size_t strlen (char const*) ; 
 int tree_write_stack_finish_subtree (struct tree_write_stack*) ; 
 int /*<<< orphan*/  tree_write_stack_init_subtree (struct tree_write_stack*,char const*) ; 
 int /*<<< orphan*/  write_tree_entry (int /*<<< orphan*/ *,unsigned int,char const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_each_note_helper(struct tree_write_stack *tws,
		const char *path, unsigned int mode,
		const struct object_id *oid)
{
	size_t path_len = strlen(path);
	unsigned int n = 0;
	int ret;

	/* Determine common part of tree write stack */
	while (tws && 3 * n < path_len &&
	       matches_tree_write_stack(tws, path + 3 * n)) {
		n++;
		tws = tws->next;
	}

	/* tws point to last matching tree_write_stack entry */
	ret = tree_write_stack_finish_subtree(tws);
	if (ret)
		return ret;

	/* Start subtrees needed to satisfy path */
	while (3 * n + 2 < path_len && path[3 * n + 2] == '/') {
		tree_write_stack_init_subtree(tws, path + 3 * n);
		n++;
		tws = tws->next;
	}

	/* There should be no more directory components in the given path */
	assert(memchr(path + 3 * n, '/', path_len - (3 * n)) == NULL);

	/* Finally add given entry to the current tree object */
	write_tree_entry(&tws->buf, mode, path + 3 * n, path_len - (3 * n),
			 oid->hash);

	return 0;
}