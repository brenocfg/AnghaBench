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
struct stat {int /*<<< orphan*/  st_dev; } ;
struct quotafile {int fd; int quotatype; int wordsize; int accmode; int /*<<< orphan*/  qfname; int /*<<< orphan*/  fsname; int /*<<< orphan*/  dev; } ;
struct group {int /*<<< orphan*/  gr_gid; } ;
struct fstab {int /*<<< orphan*/  fs_vfstype; int /*<<< orphan*/  fs_file; } ;
struct dqhdr64 {void* dqh_reclen; void* dqh_hdrlen; void* dqh_version; int /*<<< orphan*/  dqh_magic; } ;
struct dqblk64 {int dummy; } ;
typedef  int /*<<< orphan*/  dqh ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int O_ACCMODE ; 
 int O_CLOEXEC ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int QCMD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  QUOTAGROUP ; 
 char* Q_DQHDR64_MAGIC ; 
 int Q_DQHDR64_VERSION ; 
 int /*<<< orphan*/  Q_GETQUOTASIZE ; 
 int be32toh (void*) ; 
 struct quotafile* calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  fchmod (int,int) ; 
 int /*<<< orphan*/  fchown (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct quotafile*) ; 
 struct group* getgrnam (int /*<<< orphan*/ ) ; 
 int hasquota (struct fstab*,int,int /*<<< orphan*/ ,int) ; 
 void* htobe32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct dqhdr64*,int /*<<< orphan*/ ,int) ; 
 void* open (int /*<<< orphan*/ ,int,...) ; 
 scalar_t__ quotactl (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int read (int,struct dqhdr64*,int) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int write (int,struct dqhdr64*,int) ; 

struct quotafile *
quota_open(struct fstab *fs, int quotatype, int openflags)
{
	struct quotafile *qf;
	struct dqhdr64 dqh;
	struct group *grp;
	struct stat st;
	int qcmd, serrno = 0;
	int ufs;

	if ((qf = calloc(1, sizeof(*qf))) == NULL)
		return (NULL);
	qf->fd = -1;
	qf->quotatype = quotatype;
	strlcpy(qf->fsname, fs->fs_file, sizeof(qf->fsname));
	if (stat(qf->fsname, &st) != 0)
		goto error;
	qf->dev = st.st_dev;
	qcmd = QCMD(Q_GETQUOTASIZE, quotatype);
	ufs = strcmp(fs->fs_vfstype, "ufs") == 0;
	/*
	 * On UFS, hasquota() fills in qf->qfname. But we only care about
	 * this for UFS.  So we need to call hasquota() for UFS, first.
	 */
	if (ufs) {
		serrno = hasquota(fs, quotatype, qf->qfname,
		    sizeof(qf->qfname));
	}
	if (quotactl(qf->fsname, qcmd, 0, &qf->wordsize) == 0)
		return (qf);
	if (!ufs) {
		errno = 0;
		goto error;
	} else if (serrno == 0) {
		errno = EOPNOTSUPP;
		goto error;
	}
	qf->accmode = openflags & O_ACCMODE;
	if ((qf->fd = open(qf->qfname, qf->accmode|O_CLOEXEC)) < 0 &&
	    (openflags & O_CREAT) != O_CREAT)
		goto error;
	/* File open worked, so process it */
	if (qf->fd != -1) {
		qf->wordsize = 32;
		switch (read(qf->fd, &dqh, sizeof(dqh))) {
		case -1:
			goto error;
		case sizeof(dqh):
			if (strcmp(dqh.dqh_magic, Q_DQHDR64_MAGIC) != 0) {
				/* no magic, assume 32 bits */
				qf->wordsize = 32;
				return (qf);
			}
			if (be32toh(dqh.dqh_version) != Q_DQHDR64_VERSION ||
			    be32toh(dqh.dqh_hdrlen) != sizeof(struct dqhdr64) ||
			    be32toh(dqh.dqh_reclen) != sizeof(struct dqblk64)) {
				/* correct magic, wrong version / lengths */
				errno = EINVAL;
				goto error;
			}
			qf->wordsize = 64;
			return (qf);
		default:
			qf->wordsize = 32;
			return (qf);
		}
		/* not reached */
	}
	/* open failed, but O_CREAT was specified, so create a new file */
	if ((qf->fd = open(qf->qfname, O_RDWR|O_CREAT|O_TRUNC|O_CLOEXEC, 0)) <
	    0)
		goto error;
	qf->wordsize = 64;
	memset(&dqh, 0, sizeof(dqh));
	memcpy(dqh.dqh_magic, Q_DQHDR64_MAGIC, sizeof(dqh.dqh_magic));
	dqh.dqh_version = htobe32(Q_DQHDR64_VERSION);
	dqh.dqh_hdrlen = htobe32(sizeof(struct dqhdr64));
	dqh.dqh_reclen = htobe32(sizeof(struct dqblk64));
	if (write(qf->fd, &dqh, sizeof(dqh)) != sizeof(dqh)) {
		/* it was one we created ourselves */
		unlink(qf->qfname);
		goto error;
	}
	grp = getgrnam(QUOTAGROUP);
	fchown(qf->fd, 0, grp ? grp->gr_gid : 0);
	fchmod(qf->fd, 0640);
	return (qf);
error:
	serrno = errno;
	/* did we have an open file? */
	if (qf->fd != -1)
		close(qf->fd);
	free(qf);
	errno = serrno;
	return (NULL);
}