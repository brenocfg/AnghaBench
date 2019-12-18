#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* mr; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_1__* mw; TYPE_4__ bind_info; } ;
struct ibv_send_wr {scalar_t__ opcode; TYPE_2__ bind_mw; } ;
struct ibv_qp {int dummy; } ;
struct TYPE_7__ {scalar_t__ pd; } ;
struct TYPE_5__ {scalar_t__ type; scalar_t__ pd; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IBV_MW_TYPE_1 ; 
 scalar_t__ IBV_WR_BIND_MW ; 
 int _mlx5_post_send (struct ibv_qp*,struct ibv_send_wr*,struct ibv_send_wr**) ; 

int mlx5_post_send(struct ibv_qp *ibqp, struct ibv_send_wr *wr,
		   struct ibv_send_wr **bad_wr)
{
#ifdef MW_DEBUG
	if (wr->opcode == IBV_WR_BIND_MW) {
		if (wr->bind_mw.mw->type == IBV_MW_TYPE_1)
			return EINVAL;

		if (!wr->bind_mw.bind_info.mr ||
		    !wr->bind_mw.bind_info.addr ||
		    !wr->bind_mw.bind_info.length)
			return EINVAL;

		if (wr->bind_mw.bind_info.mr->pd != wr->bind_mw.mw->pd)
			return EINVAL;
	}
#endif

	return _mlx5_post_send(ibqp, wr, bad_wr);
}