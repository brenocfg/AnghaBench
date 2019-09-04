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
struct strbuf {int dummy; } ;
struct object_id {int dummy; } ;
struct diff_options {int /*<<< orphan*/  pathchange; } ;
struct combine_diff_path {struct combine_diff_path* next; } ;
typedef  int /*<<< orphan*/  pathchange_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  diff_tree_paths (struct combine_diff_path*,struct object_id const*,struct object_id const**,int,struct strbuf*,struct diff_options*) ; 
 int /*<<< orphan*/  emit_diff_first_parent_only ; 
 int /*<<< orphan*/  free (struct combine_diff_path*) ; 

__attribute__((used)) static int ll_diff_tree_oid(const struct object_id *old_oid,
			    const struct object_id *new_oid,
			    struct strbuf *base, struct diff_options *opt)
{
	struct combine_diff_path phead, *p;
	pathchange_fn_t pathchange_old = opt->pathchange;

	phead.next = NULL;
	opt->pathchange = emit_diff_first_parent_only;
	diff_tree_paths(&phead, new_oid, &old_oid, 1, base, opt);

	for (p = phead.next; p;) {
		struct combine_diff_path *pprev = p;
		p = p->next;
		free(pprev);
	}

	opt->pathchange = pathchange_old;
	return 0;
}