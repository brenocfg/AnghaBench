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
struct list_objects_filter_options {int /*<<< orphan*/  tree_exclude_depth; } ;
struct filter_trees_depth_data {scalar_t__ current_depth; int /*<<< orphan*/  exclude_depth; int /*<<< orphan*/  seen_at_depth; } ;
struct filter {int /*<<< orphan*/  free_fn; int /*<<< orphan*/  filter_object_fn; struct filter_trees_depth_data* filter_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  filter_trees_depth ; 
 int /*<<< orphan*/  filter_trees_free ; 
 int /*<<< orphan*/  oidmap_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct filter_trees_depth_data* xcalloc (int,int) ; 

__attribute__((used)) static void filter_trees_depth__init(
	struct list_objects_filter_options *filter_options,
	struct filter *filter)
{
	struct filter_trees_depth_data *d = xcalloc(1, sizeof(*d));
	oidmap_init(&d->seen_at_depth, 0);
	d->exclude_depth = filter_options->tree_exclude_depth;
	d->current_depth = 0;

	filter->filter_data = d;
	filter->filter_object_fn = filter_trees_depth;
	filter->free_fn = filter_trees_free;
}