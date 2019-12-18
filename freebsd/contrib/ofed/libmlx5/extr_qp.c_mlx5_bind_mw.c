#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ibv_mw_bind_info {int mw_access_flags; TYPE_3__* mr; scalar_t__ length; scalar_t__ addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  rkey; struct ibv_mw* mw; struct ibv_mw_bind_info bind_info; } ;
struct ibv_send_wr {TYPE_1__ bind_mw; int /*<<< orphan*/  send_flags; int /*<<< orphan*/  wr_id; int /*<<< orphan*/ * next; int /*<<< orphan*/  opcode; } ;
struct ibv_qp {int dummy; } ;
struct ibv_mw_bind {struct ibv_mw_bind_info bind_info; int /*<<< orphan*/  send_flags; int /*<<< orphan*/  wr_id; } ;
struct ibv_mw {scalar_t__ pd; int /*<<< orphan*/  rkey; } ;
struct TYPE_6__ {scalar_t__ pd; } ;
struct TYPE_5__ {int alloc_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int IBV_ACCESS_ZERO_BASED ; 
 int /*<<< orphan*/  IBV_WR_BIND_MW ; 
 int _mlx5_post_send (struct ibv_qp*,struct ibv_send_wr*,struct ibv_send_wr**) ; 
 int errno ; 
 int /*<<< orphan*/  ibv_inc_rkey (int /*<<< orphan*/ ) ; 
 TYPE_2__* to_mmr (TYPE_3__*) ; 

int mlx5_bind_mw(struct ibv_qp *qp, struct ibv_mw *mw,
		 struct ibv_mw_bind *mw_bind)
{
	struct ibv_mw_bind_info	*bind_info = &mw_bind->bind_info;
	struct ibv_send_wr wr = {};
	struct ibv_send_wr *bad_wr = NULL;
	int ret;

	if (!bind_info->mr && (bind_info->addr || bind_info->length)) {
		errno = EINVAL;
		return errno;
	}

	if (bind_info->mw_access_flags & IBV_ACCESS_ZERO_BASED) {
		errno = EINVAL;
		return errno;
	}

	if (bind_info->mr) {
		if (to_mmr(bind_info->mr)->alloc_flags & IBV_ACCESS_ZERO_BASED) {
			errno = EINVAL;
			return errno;
		}

		if (mw->pd != bind_info->mr->pd) {
			errno = EPERM;
			return errno;
		}
	}

	wr.opcode = IBV_WR_BIND_MW;
	wr.next = NULL;
	wr.wr_id = mw_bind->wr_id;
	wr.send_flags = mw_bind->send_flags;
	wr.bind_mw.bind_info = mw_bind->bind_info;
	wr.bind_mw.mw = mw;
	wr.bind_mw.rkey = ibv_inc_rkey(mw->rkey);

	ret = _mlx5_post_send(qp, &wr, &bad_wr);
	if (ret)
		return ret;

	mw->rkey = wr.bind_mw.rkey;

	return 0;
}