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
typedef  void* uintmax_t ;
struct TYPE_2__ {void* dqb_itime; void* dqb_btime; } ;
struct quotause {int flags; TYPE_1__ dqblk; struct quotause* next; int /*<<< orphan*/  fsname; } ;
typedef  int /*<<< orphan*/  line1 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int FOUND ; 
 scalar_t__ cvtatos (void*,char*,void**) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int sscanf (char*,char*,void**,char*,void**,char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 char* strtok (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

int
readtimes(struct quotause *quplist, char *inname)
{
	struct quotause *qup;
	FILE *fd;
	int cnt;
	char *cp;
	uintmax_t itime, btime, iseconds, bseconds;
	char *fsp, bunits[10], iunits[10], line1[BUFSIZ];

	fd = fopen(inname, "r");
	if (fd == NULL) {
		warnx("can't re-read temp file!!");
		return (0);
	}
	/*
	 * Discard two title lines, then read lines to process.
	 */
	(void) fgets(line1, sizeof (line1), fd);
	(void) fgets(line1, sizeof (line1), fd);
	while (fgets(line1, sizeof (line1), fd) != NULL) {
		if ((fsp = strtok(line1, " \t:")) == NULL) {
			warnx("%s: bad format", line1);
			return (0);
		}
		if ((cp = strtok((char *)0, "\n")) == NULL) {
			warnx("%s: %s: bad format", fsp, &fsp[strlen(fsp) + 1]);
			return (0);
		}
		cnt = sscanf(cp,
		    " block grace period: %ju %s file grace period: %ju %s",
		    &btime, bunits, &itime, iunits);
		if (cnt != 4) {
			warnx("%s:%s: bad format", fsp, cp);
			return (0);
		}
		if (cvtatos(btime, bunits, &bseconds) == 0)
			return (0);
		if (cvtatos(itime, iunits, &iseconds) == 0)
			return (0);
		for (qup = quplist; qup; qup = qup->next) {
			if (strcmp(fsp, qup->fsname))
				continue;
			qup->dqblk.dqb_btime = bseconds;
			qup->dqblk.dqb_itime = iseconds;
			qup->flags |= FOUND;
			break;
		}
	}
	fclose(fd);
	/*
	 * reset default grace periods for any filesystems
	 * that have not been found.
	 */
	for (qup = quplist; qup; qup = qup->next) {
		if (qup->flags & FOUND) {
			qup->flags &= ~FOUND;
			continue;
		}
		qup->dqblk.dqb_btime = 0;
		qup->dqblk.dqb_itime = 0;
	}
	return (1);
}