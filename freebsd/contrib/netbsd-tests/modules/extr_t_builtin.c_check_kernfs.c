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
 int /*<<< orphan*/  HZFILE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  RL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rump_sys_close (int) ; 
 int rump_sys_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rump_sys_read (int,char*,int) ; 

__attribute__((used)) static bool
check_kernfs(void)
{
	char buf[16];
	bool rv = true;
	int fd;

	fd = rump_sys_open(HZFILE, O_RDONLY);
	if (fd == -1)
		return false;
	if (rump_sys_read(fd, buf, sizeof(buf)) < 1)
		rv = false;
	RL(rump_sys_close(fd));

	return rv;
}