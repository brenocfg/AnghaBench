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
struct dqhdr64 {int dummy; } ;
struct dqblk64 {void* dqb_itime; void* dqb_btime; void* dqb_curinodes; void* dqb_isoftlimit; void* dqb_ihardlimit; void* dqb_curblocks; void* dqb_bsoftlimit; void* dqb_bhardlimit; } ;
struct dqblk {int /*<<< orphan*/  dqb_itime; int /*<<< orphan*/  dqb_btime; int /*<<< orphan*/  dqb_curinodes; int /*<<< orphan*/  dqb_isoftlimit; int /*<<< orphan*/  dqb_ihardlimit; int /*<<< orphan*/  dqb_curblocks; int /*<<< orphan*/  dqb_bsoftlimit; int /*<<< orphan*/  dqb_bhardlimit; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  dqb64 ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 void* htobe64 (int /*<<< orphan*/ ) ; 
 int lseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int write (int /*<<< orphan*/ ,struct dqblk64*,int) ; 

__attribute__((used)) static int
quota_write64(struct quotafile *qf, const struct dqblk *dqb, int id)
{
	struct dqblk64 dqb64;
	off_t off;

	dqb64.dqb_bhardlimit = htobe64(dqb->dqb_bhardlimit);
	dqb64.dqb_bsoftlimit = htobe64(dqb->dqb_bsoftlimit);
	dqb64.dqb_curblocks = htobe64(dqb->dqb_curblocks);
	dqb64.dqb_ihardlimit = htobe64(dqb->dqb_ihardlimit);
	dqb64.dqb_isoftlimit = htobe64(dqb->dqb_isoftlimit);
	dqb64.dqb_curinodes = htobe64(dqb->dqb_curinodes);
	dqb64.dqb_btime = htobe64(dqb->dqb_btime);
	dqb64.dqb_itime = htobe64(dqb->dqb_itime);

	off = sizeof(struct dqhdr64) + id * sizeof(struct dqblk64);
	if (lseek(qf->fd, off, SEEK_SET) == -1)
		return (-1);
	if (write(qf->fd, &dqb64, sizeof(dqb64)) == sizeof(dqb64))
		return (0);
	return (-1);
}