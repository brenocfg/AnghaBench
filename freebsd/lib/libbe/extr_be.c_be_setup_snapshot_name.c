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
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_3__ {int /*<<< orphan*/  lzh; } ;
typedef  TYPE_1__ libbe_handle_t ;

/* Variables and functions */
 int BE_SNAP_SERIAL_MAX ; 
 int /*<<< orphan*/  ZFS_TYPE_SNAPSHOT ; 
 int /*<<< orphan*/  localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int) ; 
 scalar_t__ strftime (char*,size_t,char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_dataset_exists (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
be_setup_snapshot_name(libbe_handle_t *lbh, char *buf, size_t buflen)
{
	time_t rawtime;
	int len, serial;

	time(&rawtime);
	len = strlen(buf);
	len += strftime(buf + len, buflen - len, "@%F-%T", localtime(&rawtime));
	/* No room for serial... caller will do its best */
	if (buflen - len < 2)
		return;

	for (serial = 0; serial < BE_SNAP_SERIAL_MAX; ++serial) {
		snprintf(buf + len, buflen - len, "-%d", serial);
		if (!zfs_dataset_exists(lbh->lzh, buf, ZFS_TYPE_SNAPSHOT))
			return;
	}
}