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
struct TYPE_3__ {char const* dbra_fsname; char const* dbra_oldname; char const* dbra_newname; } ;
typedef  TYPE_1__ dsl_bookmark_rename_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_SPACE_CHECK_NORMAL ; 
 int /*<<< orphan*/  dsl_bookmark_rename_check ; 
 int /*<<< orphan*/  dsl_bookmark_rename_sync ; 
 int dsl_sync_task (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

int
dsl_bookmark_rename(const char *fsname, const char *oldbmark,
    const char *newbmark)
{
	dsl_bookmark_rename_arg_t dbra;

	dbra.dbra_fsname = fsname;
	dbra.dbra_oldname = oldbmark;
	dbra.dbra_newname = newbmark;

	return (dsl_sync_task(fsname, dsl_bookmark_rename_check,
	    dsl_bookmark_rename_sync, &dbra, 1, ZFS_SPACE_CHECK_NORMAL));
}