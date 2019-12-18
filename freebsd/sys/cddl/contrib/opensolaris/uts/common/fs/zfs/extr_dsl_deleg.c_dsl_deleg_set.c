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
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_3__ {char const* dda_name; int /*<<< orphan*/ * dda_nvlist; } ;
typedef  TYPE_1__ dsl_deleg_arg_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_SPACE_CHECK_RESERVED ; 
 int /*<<< orphan*/  dsl_deleg_check ; 
 int /*<<< orphan*/  dsl_deleg_set_sync ; 
 int /*<<< orphan*/  dsl_deleg_unset_sync ; 
 int dsl_sync_task (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_num_pairs (int /*<<< orphan*/ *) ; 

int
dsl_deleg_set(const char *ddname, nvlist_t *nvp, boolean_t unset)
{
	dsl_deleg_arg_t dda;

	/* nvp must already have been verified to be valid */

	dda.dda_name = ddname;
	dda.dda_nvlist = nvp;

	return (dsl_sync_task(ddname, dsl_deleg_check,
	    unset ? dsl_deleg_unset_sync : dsl_deleg_set_sync,
	    &dda, fnvlist_num_pairs(nvp), ZFS_SPACE_CHECK_RESERVED));
}