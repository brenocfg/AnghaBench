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
struct TYPE_3__ {char const* ddra_fsname; char const* ddra_tosnap; int /*<<< orphan*/ * ddra_result; void* ddra_owner; } ;
typedef  TYPE_1__ dsl_dataset_rollback_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_SPACE_CHECK_RESERVED ; 
 int /*<<< orphan*/  dsl_dataset_rollback_check ; 
 int /*<<< orphan*/  dsl_dataset_rollback_sync ; 
 int dsl_sync_task (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

int
dsl_dataset_rollback(const char *fsname, const char *tosnap, void *owner,
    nvlist_t *result)
{
	dsl_dataset_rollback_arg_t ddra;

	ddra.ddra_fsname = fsname;
	ddra.ddra_tosnap = tosnap;
	ddra.ddra_owner = owner;
	ddra.ddra_result = result;

	return (dsl_sync_task(fsname, dsl_dataset_rollback_check,
	    dsl_dataset_rollback_sync, &ddra,
	    1, ZFS_SPACE_CHECK_RESERVED));
}