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
struct cmdinfo {int ci_calls; char* ci_comm; int ci_utime; int ci_stime; int ci_uid; int /*<<< orphan*/  ci_io; int /*<<< orphan*/  ci_mem; int /*<<< orphan*/  ci_etime; int /*<<< orphan*/  ci_flags; } ;
struct acctv3 {char* ac_comm; int ac_flagx; int ac_utime; int ac_stime; int ac_uid; int /*<<< orphan*/  ac_io; int /*<<< orphan*/  ac_mem; int /*<<< orphan*/  ac_etime; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int AFORK ; 
 int /*<<< orphan*/  CI_UNPRINTABLE ; 
 int EOF ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  isascii (char) ; 
 scalar_t__ iscntrl (char) ; 
 scalar_t__ mflag ; 
 int /*<<< orphan*/  pacct_add (struct cmdinfo*) ; 
 int /*<<< orphan*/  printf (char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  qflag ; 
 int readrec_forward (int /*<<< orphan*/ *,struct acctv3*) ; 
 scalar_t__ sflag ; 
 int /*<<< orphan*/  uflag ; 
 int /*<<< orphan*/  usracct_add (struct cmdinfo*) ; 
 int /*<<< orphan*/  warn (char*,char const*,...) ; 

__attribute__((used)) static FILE *
acct_load(const char *pn, int wr)
{
	struct acctv3 ac;
	struct cmdinfo ci;
	ssize_t rv;
	FILE *f;
	int i;

	/*
	 * open the file
	 */
	f = fopen(pn, wr ? "r+" : "r");
	if (f == NULL) {
		warn("open %s %s", pn, wr ? "for read/write" : "read-only");
		return (NULL);
	}

	/*
	 * read all we can; don't stat and open because more processes
	 * could exit, and we'd miss them
	 */
	while (1) {
		/* get one accounting entry and punt if there's an error */
		rv = readrec_forward(f, &ac);
		if (rv != 1) {
			if (rv == EOF)
				warn("error reading %s", pn);
			break;
		}

		/* decode it */
		ci.ci_calls = 1;
		for (i = 0; i < (int)sizeof ac.ac_comm && ac.ac_comm[i] != '\0';
		    i++) {
			char c = ac.ac_comm[i];

			if (!isascii(c) || iscntrl(c)) {
				ci.ci_comm[i] = '?';
				ci.ci_flags |= CI_UNPRINTABLE;
			} else
				ci.ci_comm[i] = c;
		}
		if (ac.ac_flagx & AFORK)
			ci.ci_comm[i++] = '*';
		ci.ci_comm[i++] = '\0';
		ci.ci_etime = ac.ac_etime;
		ci.ci_utime = ac.ac_utime;
		ci.ci_stime = ac.ac_stime;
		ci.ci_uid = ac.ac_uid;
		ci.ci_mem = ac.ac_mem;
		ci.ci_io = ac.ac_io;

		if (!uflag) {
			/* and enter it into the usracct and pacct databases */
			if (sflag || (!mflag && !qflag))
				pacct_add(&ci);
			if (sflag || (mflag && !qflag))
				usracct_add(&ci);
		} else if (!qflag)
			printf("%6u %12.3lf cpu %12.0lfk mem %12.0lf io %s\n",
			    ci.ci_uid,
			    (ci.ci_utime + ci.ci_stime) / 1000000,
			    ci.ci_mem, ci.ci_io,
			    ci.ci_comm);
	}

	/* Finally, return the file stream for possible truncation. */
	return (f);
}