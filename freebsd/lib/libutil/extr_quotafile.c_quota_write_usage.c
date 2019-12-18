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
struct quotafile {int fd; int accmode; int wordsize; int /*<<< orphan*/  fsname; int /*<<< orphan*/  quotatype; } ;
struct dqblk {scalar_t__ dqb_bsoftlimit; scalar_t__ dqb_curblocks; scalar_t__ dqb_isoftlimit; scalar_t__ dqb_curinodes; scalar_t__ dqb_itime; scalar_t__ dqb_btime; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  EINVAL ; 
 int O_RDWR ; 
 int QCMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_SETUSE ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ quota_read (struct quotafile*,struct dqblk*,int) ; 
 int quota_write32 (struct quotafile*,struct dqblk*,int) ; 
 int quota_write64 (struct quotafile*,struct dqblk*,int) ; 
 int quotactl (int /*<<< orphan*/ ,int,int,struct dqblk*) ; 

int
quota_write_usage(struct quotafile *qf, struct dqblk *dqb, int id)
{
	struct dqblk dqbuf;
	int qcmd;

	if (qf->fd == -1) {
		qcmd = QCMD(Q_SETUSE, qf->quotatype);
		return (quotactl(qf->fsname, qcmd, id, dqb));
	}
	/*
	 * Have to do read-modify-write of quota in file.
	 */
	if ((qf->accmode & O_RDWR) != O_RDWR) {
		errno = EBADF;
		return (-1);
	}
	if (quota_read(qf, &dqbuf, id) != 0)
		return (-1);
	/*
	 * Reset time limit if have a soft limit and were
	 * previously under it, but are now over it.
	 */
	if (dqbuf.dqb_bsoftlimit && id != 0 &&
	    dqbuf.dqb_curblocks < dqbuf.dqb_bsoftlimit &&
	    dqb->dqb_curblocks >= dqbuf.dqb_bsoftlimit)
		dqbuf.dqb_btime = 0;
	if (dqbuf.dqb_isoftlimit && id != 0 &&
	    dqbuf.dqb_curinodes < dqbuf.dqb_isoftlimit &&
	    dqb->dqb_curinodes >= dqbuf.dqb_isoftlimit)
		dqbuf.dqb_itime = 0;
	dqbuf.dqb_curinodes = dqb->dqb_curinodes;
	dqbuf.dqb_curblocks = dqb->dqb_curblocks;
	/*
	 * Write it back.
	 */
	switch (qf->wordsize) {
	case 32:
		return (quota_write32(qf, &dqbuf, id));
	case 64:
		return (quota_write64(qf, &dqbuf, id));
	default:
		errno = EINVAL;
		return (-1);
	}
	/* not reached */
}