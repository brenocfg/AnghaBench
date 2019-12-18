#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct tree_write_stack {char* path; TYPE_1__ buf; struct tree_write_stack* next; } ;
struct object_id {int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tree_write_stack*) ; 
 int /*<<< orphan*/  strbuf_release (TYPE_1__*) ; 
 int /*<<< orphan*/  tree_type ; 
 int write_object_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  write_tree_entry (TYPE_1__*,int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tree_write_stack_finish_subtree(struct tree_write_stack *tws)
{
	int ret;
	struct tree_write_stack *n = tws->next;
	struct object_id s;
	if (n) {
		ret = tree_write_stack_finish_subtree(n);
		if (ret)
			return ret;
		ret = write_object_file(n->buf.buf, n->buf.len, tree_type, &s);
		if (ret)
			return ret;
		strbuf_release(&n->buf);
		free(n);
		tws->next = NULL;
		write_tree_entry(&tws->buf, 040000, tws->path, 2, s.hash);
		tws->path[0] = tws->path[1] = '\0';
	}
	return 0;
}