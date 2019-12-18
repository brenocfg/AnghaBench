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
struct TYPE_2__ {int /*<<< orphan*/  dqb_ihardlimit; int /*<<< orphan*/  dqb_isoftlimit; int /*<<< orphan*/  dqb_curinodes; int /*<<< orphan*/  dqb_bhardlimit; int /*<<< orphan*/  dqb_bsoftlimit; int /*<<< orphan*/  dqb_curblocks; } ;
struct quotause {char* fsname; TYPE_1__ dqblk; struct quotause* next; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  L_SET ; 
 int /*<<< orphan*/  dup (int) ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int /*<<< orphan*/ ,char*) ; 
 char* fmthumanvalblks (int /*<<< orphan*/ ) ; 
 char* fmthumanvalinos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  ftruncate (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char** qfextension ; 
 int /*<<< orphan*/  tmpfil ; 

int
writeprivs(struct quotause *quplist, int outfd, char *name, int quotatype)
{
	struct quotause *qup;
	FILE *fd;

	ftruncate(outfd, 0);
	lseek(outfd, 0, L_SET);
	if ((fd = fdopen(dup(outfd), "w")) == NULL)
		err(1, "%s", tmpfil);
	fprintf(fd, "Quotas for %s %s:\n", qfextension[quotatype], name);
	for (qup = quplist; qup; qup = qup->next) {
		fprintf(fd, "%s: in use: %s, ", qup->fsname,
		    fmthumanvalblks(qup->dqblk.dqb_curblocks));
		fprintf(fd, "limits (soft = %s, ",
		    fmthumanvalblks(qup->dqblk.dqb_bsoftlimit));
		fprintf(fd, "hard = %s)\n",
		    fmthumanvalblks(qup->dqblk.dqb_bhardlimit));
		fprintf(fd, "\tinodes in use: %s, ",
		    fmthumanvalinos(qup->dqblk.dqb_curinodes));
		fprintf(fd, "limits (soft = %s, ",
		    fmthumanvalinos(qup->dqblk.dqb_isoftlimit));
		fprintf(fd, "hard = %s)\n",
		    fmthumanvalinos(qup->dqblk.dqb_ihardlimit));
	}
	fclose(fd);
	return (1);
}