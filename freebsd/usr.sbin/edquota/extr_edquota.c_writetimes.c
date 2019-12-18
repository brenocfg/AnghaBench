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
struct TYPE_2__ {int /*<<< orphan*/  dqb_itime; int /*<<< orphan*/  dqb_btime; } ;
struct quotause {char* fsname; TYPE_1__ dqblk; struct quotause* next; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  L_SET ; 
 char* cvtstoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dup (int) ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ftruncate (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char** qfextension ; 
 int /*<<< orphan*/  tmpfil ; 

int
writetimes(struct quotause *quplist, int outfd, int quotatype)
{
	struct quotause *qup;
	FILE *fd;

	ftruncate(outfd, 0);
	lseek(outfd, 0, L_SET);
	if ((fd = fdopen(dup(outfd), "w")) == NULL)
		err(1, "%s", tmpfil);
	fprintf(fd, "Time units may be: days, hours, minutes, or seconds\n");
	fprintf(fd, "Grace period before enforcing soft limits for %ss:\n",
	    qfextension[quotatype]);
	for (qup = quplist; qup; qup = qup->next) {
		fprintf(fd, "%s: block grace period: %s, ",
		    qup->fsname, cvtstoa(qup->dqblk.dqb_btime));
		fprintf(fd, "file grace period: %s\n",
		    cvtstoa(qup->dqblk.dqb_itime));
	}
	fclose(fd);
	return (1);
}