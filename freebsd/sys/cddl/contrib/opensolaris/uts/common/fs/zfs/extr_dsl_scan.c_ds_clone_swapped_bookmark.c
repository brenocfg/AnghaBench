#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ zb_objset; } ;
typedef  TYPE_1__ zbookmark_phys_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_7__ {scalar_t__ ds_object; } ;
typedef  TYPE_2__ dsl_dataset_t ;

/* Variables and functions */
 int /*<<< orphan*/  zfs_dbgmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ds_clone_swapped_bookmark(dsl_dataset_t *ds1, dsl_dataset_t *ds2,
    zbookmark_phys_t *scn_bookmark)
{
	if (scn_bookmark->zb_objset == ds1->ds_object) {
		scn_bookmark->zb_objset = ds2->ds_object;
		zfs_dbgmsg("clone_swap ds %llu; currently traversing; "
		    "reset zb_objset to %llu",
		    (u_longlong_t)ds1->ds_object,
		    (u_longlong_t)ds2->ds_object);
	} else if (scn_bookmark->zb_objset == ds2->ds_object) {
		scn_bookmark->zb_objset = ds1->ds_object;
		zfs_dbgmsg("clone_swap ds %llu; currently traversing; "
		    "reset zb_objset to %llu",
		    (u_longlong_t)ds2->ds_object,
		    (u_longlong_t)ds1->ds_object);
	}
}