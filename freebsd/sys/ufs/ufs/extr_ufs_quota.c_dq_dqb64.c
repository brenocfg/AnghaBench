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
struct dqblk64 {void* dqb_itime; void* dqb_btime; void* dqb_curinodes; void* dqb_isoftlimit; void* dqb_ihardlimit; void* dqb_curblocks; void* dqb_bsoftlimit; void* dqb_bhardlimit; } ;

/* Variables and functions */
 void* htobe64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dq_dqb64(const struct dquot *dq, struct dqblk64 *dqb64)
{

	dqb64->dqb_bhardlimit = htobe64(dq->dq_bhardlimit);
	dqb64->dqb_bsoftlimit = htobe64(dq->dq_bsoftlimit);
	dqb64->dqb_curblocks = htobe64(dq->dq_curblocks);
	dqb64->dqb_ihardlimit = htobe64(dq->dq_ihardlimit);
	dqb64->dqb_isoftlimit = htobe64(dq->dq_isoftlimit);
	dqb64->dqb_curinodes = htobe64(dq->dq_curinodes);
	dqb64->dqb_btime = htobe64(dq->dq_btime);
	dqb64->dqb_itime = htobe64(dq->dq_itime);
}