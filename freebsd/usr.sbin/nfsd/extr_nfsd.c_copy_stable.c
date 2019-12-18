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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int fsync (int) ; 
 int ftruncate (int,int /*<<< orphan*/ ) ; 
 int lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void
copy_stable(int from_fd, int to_fd)
{
	int cnt, ret;
	static char buf[1024];

	ret = lseek(from_fd, (off_t)0, SEEK_SET);
	if (ret >= 0)
		ret = lseek(to_fd, (off_t)0, SEEK_SET);
	if (ret >= 0)
		ret = ftruncate(to_fd, (off_t)0);
	if (ret >= 0)
		do {
			cnt = read(from_fd, buf, 1024);
			if (cnt > 0)
				ret = write(to_fd, buf, cnt);
			else if (cnt < 0)
				ret = cnt;
		} while (cnt > 0 && ret >= 0);
	if (ret >= 0)
		ret = fsync(to_fd);
	if (ret < 0)
		syslog(LOG_ERR, "stable restart copy failure: %m");
}