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
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _PATH_VARRUN ; 
 char* __progname ; 
 int /*<<< orphan*/  asprintf (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ atexit (int /*<<< orphan*/ ) ; 
 int errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,long) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  pidfile_cleanup ; 
 int /*<<< orphan*/ * pidfile_path ; 
 scalar_t__ pidfile_pid ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ *) ; 

int
pidfile(const char *basename)
{
	FILE *f;
	int save_errno;
	pid_t pid;

	if (basename == NULL)
		basename = __progname;

	if (pidfile_path != NULL) {
		free(pidfile_path);
		pidfile_path = NULL;
	}

	/* _PATH_VARRUN includes trailing / */
	(void) asprintf(&pidfile_path, "%s%s.pid", _PATH_VARRUN, basename);
	if (pidfile_path == NULL)
		return (-1);

	if ((f = fopen(pidfile_path, "w")) == NULL) {
		save_errno = errno;
		free(pidfile_path);
		pidfile_path = NULL;
		errno = save_errno;
		return (-1);
	}

	pid = getpid();
	if (fprintf(f, "%ld\n", (long)pid) <= 0 || fclose(f) != 0) {
		save_errno = errno;
		(void) unlink(pidfile_path);
		free(pidfile_path);
		pidfile_path = NULL;
		errno = save_errno;
		return (-1);
	}

	pidfile_pid = pid;
	if (atexit(pidfile_cleanup) < 0) {
		save_errno = errno;
		(void) unlink(pidfile_path);
		free(pidfile_path);
		pidfile_path = NULL;
		pidfile_pid = 0;
		errno = save_errno;
		return (-1);
	}

	return (0);
}