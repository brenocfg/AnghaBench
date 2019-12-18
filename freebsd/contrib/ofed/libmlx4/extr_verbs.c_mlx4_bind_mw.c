#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  rkey; int /*<<< orphan*/  bind_info; struct ibv_mw* mw; } ;
struct ibv_send_wr {TYPE_1__ bind_mw; int /*<<< orphan*/  send_flags; int /*<<< orphan*/  wr_id; int /*<<< orphan*/ * next; int /*<<< orphan*/  opcode; } ;
struct ibv_qp {int dummy; } ;
struct ibv_mw_bind {int /*<<< orphan*/  bind_info; int /*<<< orphan*/  send_flags; int /*<<< orphan*/  wr_id; } ;
struct ibv_mw {int /*<<< orphan*/  rkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_WR_BIND_MW ; 
 int /*<<< orphan*/  ibv_inc_rkey (int /*<<< orphan*/ ) ; 
 int mlx4_post_send (struct ibv_qp*,struct ibv_send_wr*,struct ibv_send_wr**) ; 

int mlx4_bind_mw(struct ibv_qp *qp, struct ibv_mw *mw,
		 struct ibv_mw_bind *mw_bind)
{
	struct ibv_send_wr *bad_wr = NULL;
	struct ibv_send_wr wr = { };
	int ret;


	wr.opcode = IBV_WR_BIND_MW;
	wr.next = NULL;

	wr.wr_id = mw_bind->wr_id;
	wr.send_flags = mw_bind->send_flags;

	wr.bind_mw.mw = mw;
	wr.bind_mw.rkey = ibv_inc_rkey(mw->rkey);
	wr.bind_mw.bind_info = mw_bind->bind_info;

	ret = mlx4_post_send(qp, &wr, &bad_wr);

	if (ret)
		return ret;

	/* updating the mw with the latest rkey. */
	mw->rkey = wr.bind_mw.rkey;

	return 0;
}