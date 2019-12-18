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
struct stat {scalar_t__ st_nlink; } ;

/* Variables and functions */
 scalar_t__ EWOULDBLOCK ; 
 int O_CLOEXEC ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int flopen (char*,int,int /*<<< orphan*/ ) ; 
 int fstat (int,struct stat*) ; 
 char* group_file ; 
 int lockfd ; 

int
gr_lock(void)
{
	if (*group_file == '\0')
		return (-1);

	for (;;) {
		struct stat st;

		lockfd = flopen(group_file, O_RDONLY|O_NONBLOCK|O_CLOEXEC, 0);
		if (lockfd == -1) {
			if (errno == EWOULDBLOCK) {
				errx(1, "the group file is busy");
			} else {
				err(1, "could not lock the group file: ");
			}
		}
		if (fstat(lockfd, &st) == -1)
			err(1, "fstat() failed: ");
		if (st.st_nlink != 0)
			break;
		close(lockfd);
		lockfd = -1;
	}
	return (lockfd);
}