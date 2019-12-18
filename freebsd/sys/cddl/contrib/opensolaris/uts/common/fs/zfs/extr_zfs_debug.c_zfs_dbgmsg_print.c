#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* zdm_msg; } ;
typedef  TYPE_1__ zfs_dbgmsg_t ;

/* Variables and functions */
 TYPE_1__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_1__* list_next (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  zfs_dbgmsgs ; 
 int /*<<< orphan*/  zfs_dbgmsgs_lock ; 

void
zfs_dbgmsg_print(const char *tag)
{
	zfs_dbgmsg_t *zdm;

	(void) printf("ZFS_DBGMSG(%s):\n", tag);
	mutex_enter(&zfs_dbgmsgs_lock);
	for (zdm = list_head(&zfs_dbgmsgs); zdm;
	    zdm = list_next(&zfs_dbgmsgs, zdm))
		(void) printf("%s\n", zdm->zdm_msg);
	mutex_exit(&zfs_dbgmsgs_lock);
}