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
struct traversal_context {int /*<<< orphan*/ * filter; void* show_data; int /*<<< orphan*/  show_object; int /*<<< orphan*/  show_commit; struct rev_info* revs; } ;
struct rev_info {int dummy; } ;
typedef  int /*<<< orphan*/  show_object_fn ;
typedef  int /*<<< orphan*/  show_commit_fn ;

/* Variables and functions */
 int /*<<< orphan*/  do_traverse (struct traversal_context*) ; 

void traverse_commit_list(struct rev_info *revs,
			  show_commit_fn show_commit,
			  show_object_fn show_object,
			  void *show_data)
{
	struct traversal_context ctx;
	ctx.revs = revs;
	ctx.show_commit = show_commit;
	ctx.show_object = show_object;
	ctx.show_data = show_data;
	ctx.filter = NULL;
	do_traverse(&ctx);
}