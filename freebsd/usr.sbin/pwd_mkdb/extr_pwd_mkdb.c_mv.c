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
 int MAXPATHLEN ; 
 int O_DIRECTORY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 char* dirname (char*) ; 
 int errno ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ fsync (int) ; 
 int open (char*,int) ; 
 scalar_t__ rename (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

void
mv(char *from, char *to)
{
	char buf[MAXPATHLEN];
	char *to_dir;
	int to_dir_fd = -1;

	/*
	 * Make sure file is safe on disk. To improve performance we will call
	 * fsync() to the directory where file lies
	 */
	if (rename(from, to) != 0 ||
	    (to_dir = dirname(to)) == NULL ||
	    (to_dir_fd = open(to_dir, O_RDONLY|O_DIRECTORY)) == -1 ||
	    fsync(to_dir_fd) != 0) {
		int sverrno = errno;
		(void)snprintf(buf, sizeof(buf), "%s to %s", from, to);
		errno = sverrno;
		if (to_dir_fd != -1)
			close(to_dir_fd);
		error(buf);
	}

	if (to_dir_fd != -1)
		close(to_dir_fd);
}