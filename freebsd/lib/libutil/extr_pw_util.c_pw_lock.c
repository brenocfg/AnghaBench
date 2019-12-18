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
 int lockfd ; 
 char* masterpasswd ; 

int
pw_lock(void)
{

	if (*masterpasswd == '\0')
		return (-1);

	/*
	 * If the master password file doesn't exist, the system is hosed.
	 * Might as well try to build one.  Set the close-on-exec bit so
	 * that users can't get at the encrypted passwords while editing.
	 * Open should allow flock'ing the file; see 4.4BSD.	XXX
	 */
	for (;;) {
		struct stat st;

		lockfd = flopen(masterpasswd, O_RDONLY|O_NONBLOCK|O_CLOEXEC, 0);
		if (lockfd == -1) {
			if (errno == EWOULDBLOCK) {
				errx(1, "the password db file is busy");
			} else {
				err(1, "could not lock the passwd file: ");
			}
		}

		/*
		 * If the password file was replaced while we were trying to
		 * get the lock, our hardlink count will be 0 and we have to
		 * close and retry.
		 */
		if (fstat(lockfd, &st) == -1)
			err(1, "fstat() failed: ");
		if (st.st_nlink != 0)
			break;
		close(lockfd);
		lockfd = -1;
	}
	return (lockfd);
}