#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pr_propname; } ;
typedef  TYPE_1__ dsl_prop_record_t ;
struct TYPE_9__ {int /*<<< orphan*/  dd_props; int /*<<< orphan*/  dd_lock; } ;
typedef  TYPE_2__ dsl_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 TYPE_1__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_1__* list_next (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static dsl_prop_record_t *
dsl_prop_record_find(dsl_dir_t *dd, const char *propname)
{
	dsl_prop_record_t *pr = NULL;

	ASSERT(MUTEX_HELD(&dd->dd_lock));

	for (pr = list_head(&dd->dd_props);
	    pr != NULL; pr = list_next(&dd->dd_props, pr)) {
		if (strcmp(pr->pr_propname, propname) == 0)
			break;
	}

	return (pr);
}