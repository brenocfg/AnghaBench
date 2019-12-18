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

/* Variables and functions */
 scalar_t__ ENOSPC ; 
 int NUMTRIES ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*,int) ; 

__attribute__((used)) static void
fill_inodes(void)
{
	char path[PATH_MAX];
	int fd, i, max;

	/*
	 * First step, fill the directory.
	 */
	i = 0;
	while (1) {
		snprintf(path, PATH_MAX, "%d", i);
		fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0600);
		if (fd < 0)
			break;
		close(fd);
		i++;
	}
	max = i;
	if (errno != ENOSPC) {
		warn("fill_inodes: open(%s)", path);
		goto teardown;
	}

	for (i = 0; i < NUMTRIES; i++) {
		fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0600);
		if (fd < 0 && errno != ENOSPC) {
			warn("fill_inodes: open(%s) after ENOSPC", path);
			goto teardown;
		}
		if (fd >= 0) {
			warnx("fill_inodes: open(%s) after ENOSPC returned "
			    " %d", path, fd);
			close(fd);
			goto teardown;
		}
	}

teardown:
	for (i = 0; i < max; i++) {
		snprintf(path, PATH_MAX, "%d", i);
		(void)unlink(path);
	}
}