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
struct oidset {int dummy; } ;
struct object {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int oidset_insert (struct oidset*,int /*<<< orphan*/ *) ; 
 int oidset_remove (struct oidset*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int filter_trees_update_omits(
	struct object *obj,
	struct oidset *omits,
	int include_it)
{
	if (!omits)
		return 0;

	if (include_it)
		return oidset_remove(omits, &obj->oid);
	else
		return oidset_insert(omits, &obj->oid);
}