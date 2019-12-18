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
struct printer {char* lock_file; char* spool_dir; char* status_file; } ;
typedef  int /*<<< orphan*/  statfile ;
typedef  int /*<<< orphan*/  lockfile ;
typedef  int /*<<< orphan*/  fline ;
typedef  enum PrinterStatus { ____Placeholder_PrinterStatus } PrinterStatus ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int LOCK_NB ; 
 int LOCK_SH ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PS_IDLE ; 
 int PS_OTHER ; 
 int PS_PRINTING ; 
 int PS_UNKNOWN ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ flock (int,int) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum PrinterStatus
get_printer_status(const struct printer *pp)
{
	char statfile[MAXPATHLEN];
	char lockfile[MAXPATHLEN];
	char fline[128];
	int fd;
	FILE *f = NULL;
	enum PrinterStatus ps = PS_UNKNOWN;

	if (pp->lock_file[0] == '/')
		strlcpy(lockfile, pp->lock_file, sizeof(lockfile));
	else
		snprintf(lockfile, sizeof(lockfile), "%s/%s",
		    pp->spool_dir, pp->lock_file);

	fd = open(lockfile, O_RDONLY);
	if (fd < 0 || flock(fd, LOCK_SH | LOCK_NB) == 0) {
		ps = PS_IDLE;
		goto LABEL_DONE;
	}

	if (pp->status_file[0] == '/')
		strlcpy(statfile, pp->status_file, sizeof(statfile));
	else
		snprintf(statfile, sizeof(statfile), "%s/%s",
		    pp->spool_dir, pp->status_file);

	f = fopen(statfile, "r");
	if (f == NULL) {
		syslog(LOG_ERR, "cannot open status file: %s", strerror(errno));
		ps = PS_UNKNOWN;
		goto LABEL_DONE;
	}

	memset(&fline[0], '\0', sizeof(fline));
	if (fgets(fline, sizeof(fline) -1, f) == NULL) {
		ps = PS_UNKNOWN;
		goto LABEL_DONE;
	}

	if (strstr(fline, "is ready and printing") != NULL) {
		ps = PS_PRINTING;
		goto LABEL_DONE;
	}

	if (strstr(fline, "to become ready (offline?)") != NULL) {
		ps = PS_OTHER;
		goto LABEL_DONE;
	}

LABEL_DONE:
	if (fd >= 0)
		(void)close(fd);	/* unlocks as well */

	if (f != NULL)
		(void)fclose(f);

	return (ps);
}