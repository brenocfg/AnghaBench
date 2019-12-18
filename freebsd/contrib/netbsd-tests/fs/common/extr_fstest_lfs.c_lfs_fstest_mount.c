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
struct lfstestargs {int /*<<< orphan*/  ta_cleanerloop; int /*<<< orphan*/  ta_cleanerthread; int /*<<< orphan*/  ta_mntpath; int /*<<< orphan*/  ta_uargs; } ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  MOUNT_LFS ; 
 int /*<<< orphan*/  cleaner ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct lfstestargs*) ; 
 int rump_sys_mkdir (char const*,int) ; 
 int rump_sys_mount (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 

int
lfs_fstest_mount(const atf_tc_t *tc, void *buf, const char *path, int flags)
{
	struct lfstestargs *args = buf;
	int res;

	res = rump_sys_mkdir(path, 0777);
	if (res == -1)
		return res;

	res = rump_sys_mount(MOUNT_LFS, path, flags, &args->ta_uargs,
	    sizeof(args->ta_uargs));
	if (res == -1)
		return res;

	strcpy(args->ta_mntpath, path);
	res = pthread_create(&args->ta_cleanerthread, NULL, cleaner, args);
	if (res)
		return res;

	/* wait for cleaner to initialize */
	sem_wait(&args->ta_cleanerloop);

	return 0;
}