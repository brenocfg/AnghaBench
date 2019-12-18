#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int buf_size; } ;
struct mlx5_ib_qp_base {TYPE_4__ ubuffer; } ;
struct TYPE_12__ {int wqe_shift; int wqe_cnt; } ;
struct TYPE_11__ {int wqe_cnt; int wqe_shift; } ;
struct TYPE_7__ {int buf_size; } ;
struct TYPE_8__ {TYPE_1__ ubuffer; } ;
struct TYPE_9__ {TYPE_2__ sq; } ;
struct mlx5_ib_qp {TYPE_6__ sq; TYPE_5__ rq; TYPE_3__ raw_packet_qp; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct mlx5_ib_create_qp {int sq_wqe_count; } ;
struct ib_qp_init_attr {scalar_t__ qp_type; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IB_QPT_RAW_PACKET ; 
 int MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ilog2 (int) ; 
 int /*<<< orphan*/  log_max_qp_sz ; 
 int /*<<< orphan*/  max_wqe_sz_sq ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int,int) ; 

__attribute__((used)) static int set_user_buf_size(struct mlx5_ib_dev *dev,
			    struct mlx5_ib_qp *qp,
			    struct mlx5_ib_create_qp *ucmd,
			    struct mlx5_ib_qp_base *base,
			    struct ib_qp_init_attr *attr)
{
	int desc_sz = 1 << qp->sq.wqe_shift;

	if (desc_sz > MLX5_CAP_GEN(dev->mdev, max_wqe_sz_sq)) {
		mlx5_ib_warn(dev, "desc_sz %d, max_sq_desc_sz %d\n",
			     desc_sz, MLX5_CAP_GEN(dev->mdev, max_wqe_sz_sq));
		return -EINVAL;
	}

	if (ucmd->sq_wqe_count && ((1 << ilog2(ucmd->sq_wqe_count)) != ucmd->sq_wqe_count)) {
		mlx5_ib_warn(dev, "sq_wqe_count %d, sq_wqe_count %d\n",
			     ucmd->sq_wqe_count, ucmd->sq_wqe_count);
		return -EINVAL;
	}

	qp->sq.wqe_cnt = ucmd->sq_wqe_count;

	if (qp->sq.wqe_cnt > (1 << MLX5_CAP_GEN(dev->mdev, log_max_qp_sz))) {
		mlx5_ib_warn(dev, "wqe_cnt %d, max_wqes %d\n",
			     qp->sq.wqe_cnt,
			     1 << MLX5_CAP_GEN(dev->mdev, log_max_qp_sz));
		return -EINVAL;
	}

	if (attr->qp_type == IB_QPT_RAW_PACKET) {
		base->ubuffer.buf_size = qp->rq.wqe_cnt << qp->rq.wqe_shift;
		qp->raw_packet_qp.sq.ubuffer.buf_size = qp->sq.wqe_cnt << 6;
	} else {
		base->ubuffer.buf_size = (qp->rq.wqe_cnt << qp->rq.wqe_shift) +
					 (qp->sq.wqe_cnt << 6);
	}

	return 0;
}