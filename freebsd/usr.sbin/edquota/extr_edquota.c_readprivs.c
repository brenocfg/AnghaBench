#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct TYPE_2__ {scalar_t__ dqb_curblocks; scalar_t__ dqb_bsoftlimit; scalar_t__ dqb_curinodes; scalar_t__ dqb_isoftlimit; void* dqb_ihardlimit; void* dqb_bhardlimit; scalar_t__ dqb_itime; scalar_t__ dqb_btime; } ;
struct quotause {int flags; TYPE_1__ dqblk; struct quotause* next; int /*<<< orphan*/  fsname; } ;
struct dqblk {scalar_t__ dqb_curblocks; scalar_t__ dqb_bsoftlimit; scalar_t__ dqb_curinodes; scalar_t__ dqb_isoftlimit; void* dqb_ihardlimit; void* dqb_bhardlimit; } ;
typedef  int /*<<< orphan*/  line2 ;
typedef  int /*<<< orphan*/  line1 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int FOUND ; 
 void* cvtblkval (int /*<<< orphan*/ ,char,char*) ; 
 void* cvtinoval (int /*<<< orphan*/ ,char,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ hflag ; 
 int sscanf (char*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 char* strtok (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

int
readprivs(struct quotause *quplist, char *inname)
{
	struct quotause *qup;
	FILE *fd;
	uintmax_t hardlimit, softlimit, curitems;
	char hardunits, softunits, curitemunits;
	int cnt;
	char *cp;
	struct dqblk dqblk;
	char *fsp, line1[BUFSIZ], line2[BUFSIZ];

	fd = fopen(inname, "r");
	if (fd == NULL) {
		warnx("can't re-read temp file!!");
		return (0);
	}
	/*
	 * Discard title line, then read pairs of lines to process.
	 */
	(void) fgets(line1, sizeof (line1), fd);
	while (fgets(line1, sizeof (line1), fd) != NULL &&
	       fgets(line2, sizeof (line2), fd) != NULL) {
		if ((fsp = strtok(line1, " \t:")) == NULL) {
			warnx("%s: bad format", line1);
			return (0);
		}
		if ((cp = strtok((char *)0, "\n")) == NULL) {
			warnx("%s: %s: bad format", fsp, &fsp[strlen(fsp) + 1]);
			return (0);
		}
		cnt = sscanf(cp,
		    " in use: %ju%c, limits (soft = %ju%c, hard = %ju%c)",
		    &curitems, &curitemunits, &softlimit, &softunits,
		    &hardlimit, &hardunits);
		/*
		 * The next three check for old-style input formats.
		 */
		if (cnt != 6)
			cnt = sscanf(cp,
			 " in use: %ju%c, limits (soft = %ju%c hard = %ju%c",
			    &curitems, &curitemunits, &softlimit,
			    &softunits, &hardlimit, &hardunits);
		if (cnt != 6)
			cnt = sscanf(cp,
			" in use: %ju%c, limits (soft = %ju%c hard = %ju%c)",
			    &curitems, &curitemunits, &softlimit,
			    &softunits, &hardlimit, &hardunits);
		if (cnt != 6)
			cnt = sscanf(cp,
			" in use: %ju%c, limits (soft = %ju%c, hard = %ju%c",
			    &curitems, &curitemunits, &softlimit,
			    &softunits, &hardlimit, &hardunits);
		if (cnt != 6) {
			warnx("%s:%s: bad format", fsp, cp);
			return (0);
		}
		dqblk.dqb_curblocks = cvtblkval(curitems, curitemunits,
		    "current block count");
		dqblk.dqb_bsoftlimit = cvtblkval(softlimit, softunits,
		    "block soft limit");
		dqblk.dqb_bhardlimit = cvtblkval(hardlimit, hardunits,
		    "block hard limit");
		if ((cp = strtok(line2, "\n")) == NULL) {
			warnx("%s: %s: bad format", fsp, line2);
			return (0);
		}
		cnt = sscanf(&cp[7],
		    " in use: %ju%c limits (soft = %ju%c, hard = %ju%c)",
		    &curitems, &curitemunits, &softlimit,
		    &softunits, &hardlimit, &hardunits);
		/*
		 * The next three check for old-style input formats.
		 */
		if (cnt != 6)
			cnt = sscanf(&cp[7],
			 " in use: %ju%c limits (soft = %ju%c hard = %ju%c",
			    &curitems, &curitemunits, &softlimit,
			    &softunits, &hardlimit, &hardunits);
		if (cnt != 6)
			cnt = sscanf(&cp[7],
			" in use: %ju%c limits (soft = %ju%c hard = %ju%c)",
			    &curitems, &curitemunits, &softlimit,
			    &softunits, &hardlimit, &hardunits);
		if (cnt != 6)
			cnt = sscanf(&cp[7],
			" in use: %ju%c limits (soft = %ju%c, hard = %ju%c",
			    &curitems, &curitemunits, &softlimit,
			    &softunits, &hardlimit, &hardunits);
		if (cnt != 6) {
			warnx("%s: %s: bad format cnt %d", fsp, &cp[7], cnt);
			return (0);
		}
		dqblk.dqb_curinodes = cvtinoval(curitems, curitemunits,
		    "current inode count");
		dqblk.dqb_isoftlimit = cvtinoval(softlimit, softunits,
		    "inode soft limit");
		dqblk.dqb_ihardlimit = cvtinoval(hardlimit, hardunits,
		    "inode hard limit");
		for (qup = quplist; qup; qup = qup->next) {
			if (strcmp(fsp, qup->fsname))
				continue;
			/*
			 * Cause time limit to be reset when the quota
			 * is next used if previously had no soft limit
			 * or were under it, but now have a soft limit
			 * and are over it.
			 */
			if (dqblk.dqb_bsoftlimit &&
			    qup->dqblk.dqb_curblocks >= dqblk.dqb_bsoftlimit &&
			    (qup->dqblk.dqb_bsoftlimit == 0 ||
			     qup->dqblk.dqb_curblocks <
			     qup->dqblk.dqb_bsoftlimit))
				qup->dqblk.dqb_btime = 0;
			if (dqblk.dqb_isoftlimit &&
			    qup->dqblk.dqb_curinodes >= dqblk.dqb_isoftlimit &&
			    (qup->dqblk.dqb_isoftlimit == 0 ||
			     qup->dqblk.dqb_curinodes <
			     qup->dqblk.dqb_isoftlimit))
				qup->dqblk.dqb_itime = 0;
			qup->dqblk.dqb_bsoftlimit = dqblk.dqb_bsoftlimit;
			qup->dqblk.dqb_bhardlimit = dqblk.dqb_bhardlimit;
			qup->dqblk.dqb_isoftlimit = dqblk.dqb_isoftlimit;
			qup->dqblk.dqb_ihardlimit = dqblk.dqb_ihardlimit;
			qup->flags |= FOUND;
			/* Humanized input returns only approximate counts */
			if (hflag ||
			    (dqblk.dqb_curblocks == qup->dqblk.dqb_curblocks &&
			     dqblk.dqb_curinodes == qup->dqblk.dqb_curinodes))
				break;
			warnx("%s: cannot change current allocation", fsp);
			break;
		}
	}
	fclose(fd);
	/*
	 * Disable quotas for any filesystems that have not been found.
	 */
	for (qup = quplist; qup; qup = qup->next) {
		if (qup->flags & FOUND) {
			qup->flags &= ~FOUND;
			continue;
		}
		qup->dqblk.dqb_bsoftlimit = 0;
		qup->dqblk.dqb_bhardlimit = 0;
		qup->dqblk.dqb_isoftlimit = 0;
		qup->dqblk.dqb_ihardlimit = 0;
	}
	return (1);
}