#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mddev ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  MDCTL_NAME ; 
 int /*<<< orphan*/  O_RDWR ; 
 char* _PATH_DEV ; 
 int md_fd ; 
 int /*<<< orphan*/  mdmaybeload () ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refresh_disk_storage_tbl (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*) ; 

int
init_disk_storage_tbl(void)
{
	char mddev[32] = "";

	/* Try to load md.ko if not loaded already */
	mdmaybeload();

	md_fd = -1;
	snprintf(mddev, sizeof(mddev) - 1, "%s%s", _PATH_DEV, MDCTL_NAME);
	if ((md_fd = open(mddev, O_RDWR)) == -1) {
		syslog(LOG_ERR, "open %s failed - will not include md(4) "
		    "info: %m", mddev);
	}

	refresh_disk_storage_tbl(1);

	return (0);
}