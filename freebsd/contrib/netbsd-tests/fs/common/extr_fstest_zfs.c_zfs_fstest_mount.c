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
typedef  int /*<<< orphan*/  tmpbuf ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 char* SRVURL ; 
 char* ZFSDEV ; 
 int errno ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 
 int system (char*) ; 

int
zfs_fstest_mount(const atf_tc_t *tc, void *buf, const char *path, int flags)
{
	char tmpbuf[128];
	int error;

	/* set up the hijack env for running zpool */
	setenv("RUMP_SERVER", SRVURL, 1);
	snprintf(tmpbuf, sizeof(tmpbuf)-1, "blanket=/dev/zfs:%s:%s",
	    ZFSDEV, path);
	setenv("RUMPHIJACK", tmpbuf, 1);
	setenv("LD_PRELOAD", "/usr/lib/librumphijack.so", 1);

	while (*path == '/')
		path++;

	/* run zpool create */
	snprintf(tmpbuf, sizeof(tmpbuf)-1, "zpool create %s %s",
	    path, ZFSDEV);
	if ((error = system(tmpbuf)) != 0) {
		errno = error;
		return -1;
	}

	return 0;
}