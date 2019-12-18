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
typedef  int /*<<< orphan*/  pb2 ;
typedef  int /*<<< orphan*/  pb ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 scalar_t__ ENOTEMPTY ; 
 int MAXPATHLEN ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  USES_DIRS ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  rump_sys_close (int) ; 
 int rump_sys_mkdir (char*,int) ; 
 int rump_sys_open (char*,int,int) ; 
 int rump_sys_rmdir (char*) ; 
 int rump_sys_unlink (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static void
dir_notempty(const atf_tc_t *tc, const char *mountpath)
{
	char pb[MAXPATHLEN], pb2[MAXPATHLEN];
	int fd, rv;

	USES_DIRS;

	/* check we can create directories */
	snprintf(pb, sizeof(pb), "%s/dir", mountpath);
	if (rump_sys_mkdir(pb, 0777) == -1)
		atf_tc_fail_errno("mkdir");

	snprintf(pb2, sizeof(pb2), "%s/dir/file", mountpath);
	fd = rump_sys_open(pb2, O_RDWR | O_CREAT, 0777);
	if (fd == -1)
		atf_tc_fail_errno("create file");
	rump_sys_close(fd);

	rv = rump_sys_rmdir(pb);
	if (rv != -1 || errno != ENOTEMPTY)
		atf_tc_fail("non-empty directory removed succesfully");

	if (rump_sys_unlink(pb2) == -1)
		atf_tc_fail_errno("cannot remove dir/file");

	if (rump_sys_rmdir(pb) == -1)
		atf_tc_fail_errno("remove directory");
}