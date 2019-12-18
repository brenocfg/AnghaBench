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
struct TYPE_3__ {char const* ddra_oldname; char const* ddra_newname; int /*<<< orphan*/  ddra_cred; } ;
typedef  TYPE_1__ dsl_dir_rename_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRED () ; 
 int /*<<< orphan*/  ZFS_SPACE_CHECK_RESERVED ; 
 int /*<<< orphan*/  dsl_dir_rename_check ; 
 int /*<<< orphan*/  dsl_dir_rename_sync ; 
 int dsl_sync_task (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 

int
dsl_dir_rename(const char *oldname, const char *newname)
{
	dsl_dir_rename_arg_t ddra;

	ddra.ddra_oldname = oldname;
	ddra.ddra_newname = newname;
	ddra.ddra_cred = CRED();

	return (dsl_sync_task(oldname,
	    dsl_dir_rename_check, dsl_dir_rename_sync, &ddra,
	    3, ZFS_SPACE_CHECK_RESERVED));
}