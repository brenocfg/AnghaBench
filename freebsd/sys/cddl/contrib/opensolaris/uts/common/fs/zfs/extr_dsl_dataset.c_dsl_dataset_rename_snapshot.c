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
struct TYPE_3__ {char const* ddrsa_fsname; char const* ddrsa_oldsnapname; char const* ddrsa_newsnapname; int /*<<< orphan*/  ddrsa_recursive; } ;
typedef  TYPE_1__ dsl_dataset_rename_snapshot_arg_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_SPACE_CHECK_RESERVED ; 
 int /*<<< orphan*/  dsl_dataset_rename_snapshot_check ; 
 int /*<<< orphan*/  dsl_dataset_rename_snapshot_sync ; 
 int dsl_sync_task (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

int
dsl_dataset_rename_snapshot(const char *fsname,
    const char *oldsnapname, const char *newsnapname, boolean_t recursive)
{
	dsl_dataset_rename_snapshot_arg_t ddrsa;

	ddrsa.ddrsa_fsname = fsname;
	ddrsa.ddrsa_oldsnapname = oldsnapname;
	ddrsa.ddrsa_newsnapname = newsnapname;
	ddrsa.ddrsa_recursive = recursive;

	return (dsl_sync_task(fsname, dsl_dataset_rename_snapshot_check,
	    dsl_dataset_rename_snapshot_sync, &ddrsa,
	    1, ZFS_SPACE_CHECK_RESERVED));
}