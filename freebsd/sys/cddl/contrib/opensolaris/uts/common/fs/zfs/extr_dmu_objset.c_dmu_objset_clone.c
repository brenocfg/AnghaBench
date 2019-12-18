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
struct TYPE_3__ {char const* doca_clone; char const* doca_origin; int /*<<< orphan*/  doca_cred; } ;
typedef  TYPE_1__ dmu_objset_clone_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRED () ; 
 int /*<<< orphan*/  ZFS_SPACE_CHECK_NORMAL ; 
 int /*<<< orphan*/  dmu_objset_clone_check ; 
 int /*<<< orphan*/  dmu_objset_clone_sync ; 
 int dsl_sync_task (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

int
dmu_objset_clone(const char *clone, const char *origin)
{
	dmu_objset_clone_arg_t doca;

	doca.doca_clone = clone;
	doca.doca_origin = origin;
	doca.doca_cred = CRED();

	return (dsl_sync_task(clone,
	    dmu_objset_clone_check, dmu_objset_clone_sync, &doca,
	    5, ZFS_SPACE_CHECK_NORMAL));
}