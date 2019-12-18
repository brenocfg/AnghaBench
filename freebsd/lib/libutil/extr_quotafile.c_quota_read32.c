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
struct quotafile {int /*<<< orphan*/  fd; } ;
struct dqblk32 {int /*<<< orphan*/  dqb_itime; int /*<<< orphan*/  dqb_btime; int /*<<< orphan*/  dqb_curinodes; int /*<<< orphan*/  dqb_isoftlimit; int /*<<< orphan*/  dqb_ihardlimit; int /*<<< orphan*/  dqb_curblocks; int /*<<< orphan*/  dqb_bsoftlimit; int /*<<< orphan*/  dqb_bhardlimit; } ;
struct dqblk {int /*<<< orphan*/  dqb_itime; int /*<<< orphan*/  dqb_btime; int /*<<< orphan*/  dqb_curinodes; int /*<<< orphan*/  dqb_isoftlimit; int /*<<< orphan*/  dqb_ihardlimit; int /*<<< orphan*/  dqb_curblocks; int /*<<< orphan*/  dqb_bsoftlimit; int /*<<< orphan*/  dqb_bhardlimit; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  dqb32 ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int lseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dqblk*,int /*<<< orphan*/ ,int) ; 
 int read (int /*<<< orphan*/ ,struct dqblk32*,int) ; 

__attribute__((used)) static int
quota_read32(struct quotafile *qf, struct dqblk *dqb, int id)
{
	struct dqblk32 dqb32;
	off_t off;

	off = id * sizeof(struct dqblk32);
	if (lseek(qf->fd, off, SEEK_SET) == -1)
		return (-1);
	switch (read(qf->fd, &dqb32, sizeof(dqb32))) {
	case 0:
		memset(dqb, 0, sizeof(*dqb));
		return (0);
	case sizeof(dqb32):
		dqb->dqb_bhardlimit = dqb32.dqb_bhardlimit;
		dqb->dqb_bsoftlimit = dqb32.dqb_bsoftlimit;
		dqb->dqb_curblocks = dqb32.dqb_curblocks;
		dqb->dqb_ihardlimit = dqb32.dqb_ihardlimit;
		dqb->dqb_isoftlimit = dqb32.dqb_isoftlimit;
		dqb->dqb_curinodes = dqb32.dqb_curinodes;
		dqb->dqb_btime = dqb32.dqb_btime;
		dqb->dqb_itime = dqb32.dqb_itime;
		return (0);
	default:
		return (-1);
	}
}