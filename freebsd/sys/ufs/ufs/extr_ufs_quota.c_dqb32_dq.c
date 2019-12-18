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
struct dquot {int /*<<< orphan*/  dq_itime; int /*<<< orphan*/  dq_btime; int /*<<< orphan*/  dq_curinodes; int /*<<< orphan*/  dq_isoftlimit; int /*<<< orphan*/  dq_ihardlimit; int /*<<< orphan*/  dq_curblocks; int /*<<< orphan*/  dq_bsoftlimit; int /*<<< orphan*/  dq_bhardlimit; } ;
struct dqblk32 {int /*<<< orphan*/  dqb_itime; int /*<<< orphan*/  dqb_btime; int /*<<< orphan*/  dqb_curinodes; int /*<<< orphan*/  dqb_isoftlimit; int /*<<< orphan*/  dqb_ihardlimit; int /*<<< orphan*/  dqb_curblocks; int /*<<< orphan*/  dqb_bsoftlimit; int /*<<< orphan*/  dqb_bhardlimit; } ;

/* Variables and functions */

__attribute__((used)) static void
dqb32_dq(const struct dqblk32 *dqb32, struct dquot *dq)
{

	dq->dq_bhardlimit = dqb32->dqb_bhardlimit;
	dq->dq_bsoftlimit = dqb32->dqb_bsoftlimit;
	dq->dq_curblocks = dqb32->dqb_curblocks;
	dq->dq_ihardlimit = dqb32->dqb_ihardlimit;
	dq->dq_isoftlimit = dqb32->dqb_isoftlimit;
	dq->dq_curinodes = dqb32->dqb_curinodes;
	dq->dq_btime = dqb32->dqb_btime;
	dq->dq_itime = dqb32->dqb_itime;
}