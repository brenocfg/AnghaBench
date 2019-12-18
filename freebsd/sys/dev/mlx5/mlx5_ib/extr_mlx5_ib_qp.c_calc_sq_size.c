#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5_wqe_inline_seg {int dummy; } ;
struct TYPE_4__ {int wqe_cnt; int max_post; int /*<<< orphan*/  max_gs; int /*<<< orphan*/  wqe_shift; } ;
struct mlx5_ib_qp {int max_inline_data; int signature_en; TYPE_2__ sq; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct TYPE_3__ {int max_send_wr; int max_inline_data; int /*<<< orphan*/  max_send_sge; } ;
struct ib_qp_init_attr {int create_flags; TYPE_1__ cap; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int IB_QP_CREATE_SIGNATURE_EN ; 
 int MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_SEND_WQE_BB ; 
 int calc_send_wqe (struct ib_qp_init_attr*) ; 
 int /*<<< orphan*/  get_send_sge (struct ib_qp_init_attr*,int) ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int /*<<< orphan*/  log_max_qp_sz ; 
 int /*<<< orphan*/  max_wqe_sz_sq ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,int,...) ; 
 int roundup_pow_of_two (int) ; 
 int sq_overhead (struct ib_qp_init_attr*) ; 

__attribute__((used)) static int calc_sq_size(struct mlx5_ib_dev *dev, struct ib_qp_init_attr *attr,
			struct mlx5_ib_qp *qp)
{
	int wqe_size;
	int wq_size;

	if (!attr->cap.max_send_wr)
		return 0;

	wqe_size = calc_send_wqe(attr);
	mlx5_ib_dbg(dev, "wqe_size %d\n", wqe_size);
	if (wqe_size < 0)
		return wqe_size;

	if (wqe_size > MLX5_CAP_GEN(dev->mdev, max_wqe_sz_sq)) {
		mlx5_ib_dbg(dev, "wqe_size(%d) > max_sq_desc_sz(%d)\n",
			    wqe_size, MLX5_CAP_GEN(dev->mdev, max_wqe_sz_sq));
		return -EINVAL;
	}

	qp->max_inline_data = wqe_size - sq_overhead(attr) -
			      sizeof(struct mlx5_wqe_inline_seg);
	attr->cap.max_inline_data = qp->max_inline_data;

	if (attr->create_flags & IB_QP_CREATE_SIGNATURE_EN)
		qp->signature_en = true;

	wq_size = roundup_pow_of_two(attr->cap.max_send_wr * wqe_size);
	qp->sq.wqe_cnt = wq_size / MLX5_SEND_WQE_BB;
	if (qp->sq.wqe_cnt > (1 << MLX5_CAP_GEN(dev->mdev, log_max_qp_sz))) {
		mlx5_ib_dbg(dev, "wqe count(%d) exceeds limits(%d)\n",
			    qp->sq.wqe_cnt,
			    1 << MLX5_CAP_GEN(dev->mdev, log_max_qp_sz));
		return -ENOMEM;
	}
	qp->sq.wqe_shift = ilog2(MLX5_SEND_WQE_BB);
	qp->sq.max_gs = get_send_sge(attr, wqe_size);
	if (qp->sq.max_gs < attr->cap.max_send_sge)
		return -ENOMEM;

	attr->cap.max_send_sge = qp->sq.max_gs;
	qp->sq.max_post = wq_size / wqe_size;
	attr->cap.max_send_wr = qp->sq.max_post;

	return wq_size;
}