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
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 int getpid () ; 
 scalar_t__ os_daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 struct pidfh* pidfile_open (char const*,int,scalar_t__*) ; 
 int /*<<< orphan*/  pidfile_remove (struct pidfh*) ; 
 int /*<<< orphan*/  pidfile_write (struct pidfh*) ; 
 int /*<<< orphan*/  warn (char*) ; 

int os_daemonize(const char *pid_file)
{
#if defined(__uClinux__) || defined(__sun__)
	return -1;
#else /* defined(__uClinux__) || defined(__sun__) */
#ifdef __FreeBSD__
	pid_t otherpid;
	struct pidfh *pfh;

	pfh = pidfile_open(pid_file, 0600, &otherpid);
	if (pfh == NULL) {
		if (errno == EEXIST) {
			errx(1, "Daemon already running, pid: %jd.",
			    (intmax_t)otherpid);
		}
		warn("Cannot open or create pidfile.");
	}
#endif /* __FreeBSD__ */

	if (os_daemon(0, 0)) {
		perror("daemon");
#ifdef __FreeBSD__
		pidfile_remove(pfh);
#endif /* __FreeBSD__ */
		return -1;
	}

#ifndef __FreeBSD__
	if (pid_file) {
		FILE *f = fopen(pid_file, "w");
		if (f) {
			fprintf(f, "%u\n", getpid());
			fclose(f);
		}
	}
#else /* __FreeBSD__ */
	pidfile_write(pfh);
#endif /* __FreeBSD__ */

	return -0;
#endif /* defined(__uClinux__) || defined(__sun__) */
}