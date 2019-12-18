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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EPROGMISMATCH ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  MSTR ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  RL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*) ; 
 int errno ; 
 int /*<<< orphan*/  rump_sys_close (int) ; 
 int rump_sys_open (char*,int /*<<< orphan*/ ) ; 
 int rump_sys_read (int,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

__attribute__((used)) static int
xread_tfile(const char *mp, const char *path)
{
	char pathb[MAXPATHLEN];
	char buf[128];
	int fd;

	strcpy(pathb, mp);
	strcat(pathb, "/");
	strcat(pathb, path);

	fd = rump_sys_open(pathb, O_RDONLY);
	if (fd == -1)
		return errno;
	if (rump_sys_read(fd, buf, sizeof(buf)) == -1)
		atf_tc_fail_errno("read tfile");
	RL(rump_sys_close(fd));
	if (strcmp(buf, MSTR) == 0)
		return 0;
	return EPROGMISMATCH;
}