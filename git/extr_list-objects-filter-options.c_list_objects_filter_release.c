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
struct list_objects_filter_options {size_t sub_nr; struct list_objects_filter_options* sub; struct list_objects_filter_options* sparse_oid_name; int /*<<< orphan*/  filter_spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct list_objects_filter_options*) ; 
 int /*<<< orphan*/  memset (struct list_objects_filter_options*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  string_list_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void list_objects_filter_release(
	struct list_objects_filter_options *filter_options)
{
	size_t sub;

	if (!filter_options)
		return;
	string_list_clear(&filter_options->filter_spec, /*free_util=*/0);
	free(filter_options->sparse_oid_name);
	for (sub = 0; sub < filter_options->sub_nr; sub++)
		list_objects_filter_release(&filter_options->sub[sub]);
	free(filter_options->sub);
	memset(filter_options, 0, sizeof(*filter_options));
}