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
struct quotause {struct quotause* next; int /*<<< orphan*/  dqblk; int /*<<< orphan*/  fsname; struct quotafile* qf; } ;
struct quotafile {int dummy; } ;
struct fstab {char* fs_spec; char* fs_file; char* fs_vfstype; } ;

/* Variables and functions */
 scalar_t__ EOPNOTSUPP ; 
 int O_CREAT ; 
 int O_RDWR ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  endfsent () ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  freeprivs (struct quotause*) ; 
 struct fstab* getfsent () ; 
 struct quotafile* quota_open (struct fstab*,int,int) ; 
 int quota_read (struct quotafile*,int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  setfsent () ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

struct quotause *
getprivs(long id, int quotatype, char *fspath)
{
	struct quotafile *qf;
	struct fstab *fs;
	struct quotause *qup, *quptail;
	struct quotause *quphead;

	setfsent();
	quphead = quptail = NULL;
	while ((fs = getfsent())) {
		if (fspath && *fspath && strcmp(fspath, fs->fs_spec) &&
		    strcmp(fspath, fs->fs_file))
			continue;
		if (strcmp(fs->fs_vfstype, "ufs"))
			continue;
		if ((qf = quota_open(fs, quotatype, O_CREAT|O_RDWR)) == NULL) {
			if (errno != EOPNOTSUPP)
				warn("cannot open quotas on %s", fs->fs_file);
			continue;
		}
		if ((qup = (struct quotause *)calloc(1, sizeof(*qup))) == NULL)
			errx(2, "out of memory");
		qup->qf = qf;
		strlcpy(qup->fsname, fs->fs_file, sizeof(qup->fsname));
		if (quota_read(qf, &qup->dqblk, id) == -1) {
			warn("cannot read quotas on %s", fs->fs_file);
			freeprivs(qup);
			continue;
		}
		if (quphead == NULL)
			quphead = qup;
		else
			quptail->next = qup;
		quptail = qup;
		qup->next = 0;
	}
	if (quphead == NULL) {
		warnx("No quotas on %s", fspath ? fspath : "any filesystems");
	}
	endfsent();
	return (quphead);
}