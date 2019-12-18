#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_ib_ucontext {int /*<<< orphan*/  tdn; } ;
struct TYPE_14__ {int /*<<< orphan*/  qpn; } ;
struct TYPE_15__ {TYPE_5__ mqp; struct mlx5_ib_qp* container_mibqp; } ;
struct mlx5_ib_sq {TYPE_6__ base; } ;
struct TYPE_16__ {int /*<<< orphan*/  qpn; } ;
struct TYPE_17__ {TYPE_7__ mqp; struct mlx5_ib_qp* container_mibqp; } ;
struct mlx5_ib_rq {TYPE_8__ base; } ;
struct mlx5_ib_raw_packet_qp {struct mlx5_ib_rq rq; struct mlx5_ib_sq sq; } ;
struct TYPE_18__ {scalar_t__ wqe_cnt; } ;
struct TYPE_11__ {int /*<<< orphan*/  qpn; } ;
struct TYPE_12__ {TYPE_2__ mqp; } ;
struct TYPE_13__ {TYPE_3__ base; } ;
struct TYPE_10__ {scalar_t__ wqe_cnt; } ;
struct mlx5_ib_qp {TYPE_9__ sq; TYPE_4__ trans_qp; TYPE_1__ rq; struct mlx5_ib_raw_packet_qp raw_packet_qp; } ;
struct mlx5_ib_dev {int dummy; } ;
struct ib_uobject {struct ib_ucontext* context; } ;
struct ib_ucontext {int dummy; } ;
struct ib_pd {struct ib_uobject* uobject; } ;

/* Variables and functions */
 int create_raw_packet_qp_rq (struct mlx5_ib_dev*,struct mlx5_ib_rq*,int /*<<< orphan*/ *) ; 
 int create_raw_packet_qp_sq (struct mlx5_ib_dev*,struct mlx5_ib_sq*,int /*<<< orphan*/ *,struct ib_pd*) ; 
 int create_raw_packet_qp_tir (struct mlx5_ib_dev*,struct mlx5_ib_rq*,int /*<<< orphan*/ ) ; 
 int create_raw_packet_qp_tis (struct mlx5_ib_dev*,struct mlx5_ib_sq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_raw_packet_qp_rq (struct mlx5_ib_dev*,struct mlx5_ib_rq*) ; 
 int /*<<< orphan*/  destroy_raw_packet_qp_sq (struct mlx5_ib_dev*,struct mlx5_ib_sq*) ; 
 int /*<<< orphan*/  destroy_raw_packet_qp_tis (struct mlx5_ib_dev*,struct mlx5_ib_sq*) ; 
 struct mlx5_ib_ucontext* to_mucontext (struct ib_ucontext*) ; 

__attribute__((used)) static int create_raw_packet_qp(struct mlx5_ib_dev *dev, struct mlx5_ib_qp *qp,
				u32 *in,
				struct ib_pd *pd)
{
	struct mlx5_ib_raw_packet_qp *raw_packet_qp = &qp->raw_packet_qp;
	struct mlx5_ib_sq *sq = &raw_packet_qp->sq;
	struct mlx5_ib_rq *rq = &raw_packet_qp->rq;
	struct ib_uobject *uobj = pd->uobject;
	struct ib_ucontext *ucontext = uobj->context;
	struct mlx5_ib_ucontext *mucontext = to_mucontext(ucontext);
	int err;
	u32 tdn = mucontext->tdn;

	if (qp->sq.wqe_cnt) {
		err = create_raw_packet_qp_tis(dev, sq, tdn);
		if (err)
			return err;

		err = create_raw_packet_qp_sq(dev, sq, in, pd);
		if (err)
			goto err_destroy_tis;

		sq->base.container_mibqp = qp;
	}

	if (qp->rq.wqe_cnt) {
		rq->base.container_mibqp = qp;

		err = create_raw_packet_qp_rq(dev, rq, in);
		if (err)
			goto err_destroy_sq;


		err = create_raw_packet_qp_tir(dev, rq, tdn);
		if (err)
			goto err_destroy_rq;
	}

	qp->trans_qp.base.mqp.qpn = qp->sq.wqe_cnt ? sq->base.mqp.qpn :
						     rq->base.mqp.qpn;

	return 0;

err_destroy_rq:
	destroy_raw_packet_qp_rq(dev, rq);
err_destroy_sq:
	if (!qp->sq.wqe_cnt)
		return err;
	destroy_raw_packet_qp_sq(dev, sq);
err_destroy_tis:
	destroy_raw_packet_qp_tis(dev, sq);

	return err;
}