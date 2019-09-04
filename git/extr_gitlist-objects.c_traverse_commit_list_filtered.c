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
struct traversal_context {scalar_t__ filter_data; int /*<<< orphan*/ * filter_fn; void* show_data; int /*<<< orphan*/  show_commit; int /*<<< orphan*/  show_object; struct rev_info* revs; } ;
struct rev_info {int dummy; } ;
struct oidset {int dummy; } ;
struct list_objects_filter_options {int dummy; } ;
typedef  int /*<<< orphan*/  show_object_fn ;
typedef  int /*<<< orphan*/  show_commit_fn ;
typedef  int /*<<< orphan*/  (* filter_free_fn ) (scalar_t__) ;

/* Variables and functions */
 int /*<<< orphan*/  do_traverse (struct traversal_context*) ; 
 scalar_t__ list_objects_filter__init (struct oidset*,struct list_objects_filter_options*,int /*<<< orphan*/ **,int /*<<< orphan*/  (*) (scalar_t__)) ; 

void traverse_commit_list_filtered(
	struct list_objects_filter_options *filter_options,
	struct rev_info *revs,
	show_commit_fn show_commit,
	show_object_fn show_object,
	void *show_data,
	struct oidset *omitted)
{
	struct traversal_context ctx;
	filter_free_fn filter_free_fn = NULL;

	ctx.revs = revs;
	ctx.show_object = show_object;
	ctx.show_commit = show_commit;
	ctx.show_data = show_data;
	ctx.filter_fn = NULL;

	ctx.filter_data = list_objects_filter__init(omitted, filter_options,
						    &ctx.filter_fn, &filter_free_fn);
	do_traverse(&ctx);
	if (ctx.filter_data && filter_free_fn)
		filter_free_fn(ctx.filter_data);
}