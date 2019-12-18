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
struct pidfh {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int errno ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 struct pidfh* pidfile_open (char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pidfile_remove (struct pidfh*) ; 

__attribute__((used)) static void
open_pid_files(const char *pidfile, const char *ppidfile,
	       struct pidfh **pfh, struct pidfh **ppfh)
{
	pid_t fpid;
	int serrno;

	if (pidfile) {
		*pfh = pidfile_open(pidfile, 0600, &fpid);
		if (*pfh == NULL) {
			if (errno == EEXIST) {
				errx(3, "process already running, pid: %d",
				    fpid);
			}
			err(2, "pidfile ``%s''", pidfile);
		}
	}
	/* Do the same for the actual daemon process. */
	if (ppidfile) {
		*ppfh = pidfile_open(ppidfile, 0600, &fpid);
		if (*ppfh == NULL) {
			serrno = errno;
			pidfile_remove(*pfh);
			errno = serrno;
			if (errno == EEXIST) {
				errx(3, "process already running, pid: %d",
				     fpid);
			}
			err(2, "ppidfile ``%s''", ppidfile);
		}
	}
}