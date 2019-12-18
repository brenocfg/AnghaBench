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
typedef  int uintmax_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  scalar_t__ time_t ;
struct TYPE_2__ {scalar_t__ dqb_ihardlimit; scalar_t__ dqb_curinodes; scalar_t__ dqb_isoftlimit; scalar_t__ dqb_itime; scalar_t__ dqb_bhardlimit; scalar_t__ dqb_curblocks; scalar_t__ dqb_bsoftlimit; scalar_t__ dqb_btime; } ;
struct quotause {char* fsname; TYPE_1__ dqblk; struct quotause* next; } ;

/* Variables and functions */
 scalar_t__ dbtob (scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct quotause* getprivs (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  heading (int,int /*<<< orphan*/ ,char const*,char*) ; 
 scalar_t__ hflag ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  prthumanval (int,scalar_t__) ; 
 scalar_t__ qflag ; 
 scalar_t__ rflag ; 
 int /*<<< orphan*/  showrawquotas (int,int /*<<< orphan*/ ,struct quotause*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 
 char* timeprt (scalar_t__) ; 
 int /*<<< orphan*/  vflag ; 

__attribute__((used)) static int
showquotas(int type, u_long id, const char *name)
{
	struct quotause *qup;
	struct quotause *quplist;
	const char *msgi, *msgb;
	const char *nam;
	char *bgrace = NULL, *igrace = NULL;
	int lines = 0, overquota = 0;
	static time_t now;

	if (now == 0)
		time(&now);
	quplist = getprivs(id, type);
	for (qup = quplist; qup; qup = qup->next) {
		msgi = NULL;
		if (qup->dqblk.dqb_ihardlimit &&
		    qup->dqblk.dqb_curinodes >= qup->dqblk.dqb_ihardlimit) {
			overquota++;
			msgi = "File limit reached on";
		}
		else if (qup->dqblk.dqb_isoftlimit &&
		    qup->dqblk.dqb_curinodes >= qup->dqblk.dqb_isoftlimit) {
			overquota++;
			if (qup->dqblk.dqb_itime > now)
				msgi = "In file grace period on";
			else
				msgi = "Over file quota on";
		}
		msgb = NULL;
		if (qup->dqblk.dqb_bhardlimit &&
		    qup->dqblk.dqb_curblocks >= qup->dqblk.dqb_bhardlimit) {
			overquota++;
			msgb = "Block limit reached on";
		}
		else if (qup->dqblk.dqb_bsoftlimit &&
		    qup->dqblk.dqb_curblocks >= qup->dqblk.dqb_bsoftlimit) {
			overquota++;
			if (qup->dqblk.dqb_btime > now)
				msgb = "In block grace period on";
			else
				msgb = "Over block quota on";
		}
		if (rflag) {
			showrawquotas(type, id, qup);
			continue;
		}
		if (!vflag &&
		    qup->dqblk.dqb_isoftlimit == 0 &&
		    qup->dqblk.dqb_ihardlimit == 0 &&
		    qup->dqblk.dqb_bsoftlimit == 0 &&
		    qup->dqblk.dqb_bhardlimit == 0)
			continue;
		if (qflag) {
			if ((msgi != NULL || msgb != NULL) &&
			    lines++ == 0)
				heading(type, id, name, "");
			if (msgi != NULL)
				printf("\t%s %s\n", msgi, qup->fsname);
			if (msgb != NULL)
				printf("\t%s %s\n", msgb, qup->fsname);
			continue;
		}
		if (!vflag &&
		    qup->dqblk.dqb_curblocks == 0 &&
		    qup->dqblk.dqb_curinodes == 0)
			continue;
		if (lines++ == 0)
			heading(type, id, name, "");
		nam = qup->fsname;
		if (strlen(qup->fsname) > 15) {
			printf("%s\n", qup->fsname);
			nam = "";
		} 
		printf("%-15s", nam);
		if (hflag) {
			prthumanval(7, dbtob(qup->dqblk.dqb_curblocks));
			printf("%c", (msgb == NULL) ? ' ' : '*');
			prthumanval(7, dbtob(qup->dqblk.dqb_bsoftlimit));
			prthumanval(7, dbtob(qup->dqblk.dqb_bhardlimit));
		} else {
			printf(" %7ju%c %7ju %7ju",
			    (uintmax_t)dbtob(qup->dqblk.dqb_curblocks)
				/ 1024,
			    (msgb == NULL) ? ' ' : '*',
			    (uintmax_t)dbtob(qup->dqblk.dqb_bsoftlimit)
				/ 1024,
			    (uintmax_t)dbtob(qup->dqblk.dqb_bhardlimit)
				/ 1024);
		}
		if (msgb != NULL)
			bgrace = timeprt(qup->dqblk.dqb_btime);
		if (msgi != NULL)
			igrace = timeprt(qup->dqblk.dqb_itime);
		printf("%8s %6ju%c %6ju %6ju%8s\n"
			, (msgb == NULL) ? "" : bgrace
			, (uintmax_t)qup->dqblk.dqb_curinodes
			, (msgi == NULL) ? ' ' : '*'
			, (uintmax_t)qup->dqblk.dqb_isoftlimit
			, (uintmax_t)qup->dqblk.dqb_ihardlimit
			, (msgi == NULL) ? "" : igrace
		);
		if (msgb != NULL)
			free(bgrace);
		if (msgi != NULL)
			free(igrace);
	}
	if (!qflag && !rflag && lines == 0)
		heading(type, id, name, "none");
	return (overquota);
}