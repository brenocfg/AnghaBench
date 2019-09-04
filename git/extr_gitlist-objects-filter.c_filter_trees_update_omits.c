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
struct object {int /*<<< orphan*/  oid; } ;
struct filter_trees_depth_data {int /*<<< orphan*/  omits; } ;

/* Variables and functions */
 int oidset_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int oidset_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int filter_trees_update_omits(
	struct object *obj,
	struct filter_trees_depth_data *filter_data,
	int include_it)
{
	if (!filter_data->omits)
		return 0;

	if (include_it)
		return oidset_remove(filter_data->omits, &obj->oid);
	else
		return oidset_insert(filter_data->omits, &obj->oid);
}