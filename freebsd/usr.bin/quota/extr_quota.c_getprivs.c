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
struct statfs {char* f_mntonname; char* f_fstypename; int /*<<< orphan*/  f_mntfromname; } ;
struct quotause {struct quotause* next; int /*<<< orphan*/  fsname; } ;
struct fstab {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MNT_NOWAIT ; 
 int /*<<< orphan*/  endfsent () ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/ * filename ; 
 int /*<<< orphan*/  free (struct quotause*) ; 
 struct fstab* getfsspec (int /*<<< orphan*/ ) ; 
 int getmntinfo (struct statfs**,int /*<<< orphan*/ ) ; 
 scalar_t__ getnfsquota (struct statfs*,struct quotause*,long,int) ; 
 scalar_t__ getufsquota (struct fstab*,struct quotause*,long,int) ; 
 scalar_t__ lflag ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  setfsent () ; 
 scalar_t__ statfs (int /*<<< orphan*/ *,struct statfs*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct quotause *
getprivs(long id, int quotatype)
{
	struct quotause *qup, *quptail = NULL;
	struct fstab *fs;
	struct quotause *quphead;
	struct statfs *fst;
	int nfst, i;
	struct statfs sfb;

	qup = quphead = (struct quotause *)0;

	if (filename != NULL && statfs(filename, &sfb) != 0)
		err(1, "cannot statfs %s", filename);
	nfst = getmntinfo(&fst, MNT_NOWAIT);
	if (nfst == 0)
		errx(2, "no filesystems mounted!");
	setfsent();
	for (i = 0; i < nfst; i++) {
		if (qup == NULL) {
			if ((qup = (struct quotause *)malloc(sizeof *qup))
			    == NULL)
				errx(2, "out of memory");
		}
		/*
		 * See if the user requested a specific file system
		 * or specified a file inside a mounted file system.
		 */
		if (filename != NULL &&
		    strcmp(sfb.f_mntonname, fst[i].f_mntonname) != 0)
			continue;
		if (strcmp(fst[i].f_fstypename, "nfs") == 0) {
			if (lflag)
				continue;
			if (getnfsquota(&fst[i], qup, id, quotatype) == 0)
				continue;
		} else if (strcmp(fst[i].f_fstypename, "ufs") == 0) {
			/*
			 * XXX
			 * UFS filesystems must be in /etc/fstab, and must
			 * indicate that they have quotas on (?!) This is quite
			 * unlike SunOS where quotas can be enabled/disabled
			 * on a filesystem independent of /etc/fstab, and it
			 * will still print quotas for them.
			 */
			if ((fs = getfsspec(fst[i].f_mntfromname)) == NULL)
				continue;
			if (getufsquota(fs, qup, id, quotatype) == 0)
				continue;
		} else
			continue;
		strcpy(qup->fsname, fst[i].f_mntonname);
		if (quphead == NULL)
			quphead = qup;
		else
			quptail->next = qup;
		quptail = qup;
		quptail->next = 0;
		qup = NULL;
	}
	if (qup)
		free(qup);
	endfsent();
	return (quphead);
}