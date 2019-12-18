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
struct sigwork_entry {scalar_t__ sw_runcmd; int sw_pidok; scalar_t__ sw_pid; char* sw_fname; int sw_signum; char* sw_pidtype; } ;

/* Variables and functions */
 scalar_t__ ESRCH ; 
 struct sigwork_entry* SLIST_NEXT (struct sigwork_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int kill (scalar_t__,int) ; 
 scalar_t__ noaction ; 
 scalar_t__ nosignal ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rotatereq ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  sw_nextp ; 
 int system (char*) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  warn (char*,char*,...) ; 
 int /*<<< orphan*/  warnx (char*,char*,int) ; 

__attribute__((used)) static void
do_sigwork(struct sigwork_entry *swork)
{
	struct sigwork_entry *nextsig;
	int kres, secs;
	char *tmp;

	if (swork->sw_runcmd == 0 && (!(swork->sw_pidok) || swork->sw_pid == 0))
		return;			/* no work to do... */

	/*
	 * If nosignal (-s) was specified, then do not signal any process.
	 * Note that a nosignal request triggers a warning message if the
	 * rotated logfile needs to be compressed, *unless* -R was also
	 * specified.  We assume that an `-sR' request came from a process
	 * which writes to the logfile, and as such, we assume that process
	 * has already made sure the logfile is not presently in use.  This
	 * just sets swork->sw_pidok to a special value, and do_zipwork
	 * will print any necessary warning(s).
	 */
	if (nosignal) {
		if (!rotatereq)
			swork->sw_pidok = -1;
		return;
	}

	/*
	 * Compute the pause between consecutive signals.  Use a longer
	 * sleep time if we will be sending two signals to the same
	 * daemon or process-group.
	 */
	secs = 0;
	nextsig = SLIST_NEXT(swork, sw_nextp);
	if (nextsig != NULL) {
		if (swork->sw_pid == nextsig->sw_pid)
			secs = 10;
		else
			secs = 1;
	}

	if (noaction) {
		if (swork->sw_runcmd)
			printf("\tsh -c '%s %d'\n", swork->sw_fname,
			    swork->sw_signum);
		else {
			printf("\tkill -%d %d \t\t# %s\n", swork->sw_signum,
			    (int)swork->sw_pid, swork->sw_fname);
			if (secs > 0)
				printf("\tsleep %d\n", secs);
		}
		return;
	}

	if (swork->sw_runcmd) {
		asprintf(&tmp, "%s %d", swork->sw_fname, swork->sw_signum);
		if (tmp == NULL) {
			warn("can't allocate memory to run %s",
			    swork->sw_fname);
			return;
		}
		if (verbose)
			printf("Run command: %s\n", tmp);
		kres = system(tmp);
		if (kres) {
			warnx("%s: returned non-zero exit code: %d",
			    tmp, kres);
		}
		free(tmp);
		return;
	}

	kres = kill(swork->sw_pid, swork->sw_signum);
	if (kres != 0) {
		/*
		 * Assume that "no such process" (ESRCH) is something
		 * to warn about, but is not an error.  Presumably the
		 * process which writes to the rotated log file(s) is
		 * gone, in which case we should have no problem with
		 * compressing the rotated log file(s).
		 */
		if (errno != ESRCH)
			swork->sw_pidok = 0;
		warn("can't notify %s, pid %d = %s", swork->sw_pidtype,
		    (int)swork->sw_pid, swork->sw_fname);
	} else {
		if (verbose)
			printf("Notified %s pid %d = %s\n", swork->sw_pidtype,
			    (int)swork->sw_pid, swork->sw_fname);
		if (secs > 0) {
			if (verbose)
				printf("Pause %d second(s) between signals\n",
				    secs);
			sleep(secs);
		}
	}
}