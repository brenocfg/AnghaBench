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
struct mlx5_wqe_umr_ctrl_seg {int dummy; } ;
struct mlx5_wqe_data_seg {int dummy; } ;
struct mlx5_mkey_seg {int dummy; } ;
struct TYPE_6__ {void* qend; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; int /*<<< orphan*/  pd; } ;
struct mlx5_ib_qp {TYPE_3__ sq; TYPE_2__ ibqp; } ;
struct mlx5_ib_pd {int dummy; } ;
struct mlx5_ib_mr {int dummy; } ;
struct TYPE_4__ {int send_flags; } ;
struct ib_reg_wr {int /*<<< orphan*/  access; int /*<<< orphan*/  key; TYPE_1__ wr; int /*<<< orphan*/  mr; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_SEND_INLINE ; 
 void* mlx5_get_send_wqe (struct mlx5_ib_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_reg_data_seg (void*,struct mlx5_ib_mr*,struct mlx5_ib_pd*) ; 
 int /*<<< orphan*/  set_reg_mkey_seg (void*,struct mlx5_ib_mr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_reg_umr_seg (void*,struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_mr* to_mmr (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_pd* to_mpd (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int set_reg_wr(struct mlx5_ib_qp *qp,
		      struct ib_reg_wr *wr,
		      void **seg, int *size)
{
	struct mlx5_ib_mr *mr = to_mmr(wr->mr);
	struct mlx5_ib_pd *pd = to_mpd(qp->ibqp.pd);

	if (unlikely(wr->wr.send_flags & IB_SEND_INLINE)) {
		mlx5_ib_warn(to_mdev(qp->ibqp.device),
			     "Invalid IB_SEND_INLINE send flag\n");
		return -EINVAL;
	}

	set_reg_umr_seg(*seg, mr);
	*seg += sizeof(struct mlx5_wqe_umr_ctrl_seg);
	*size += sizeof(struct mlx5_wqe_umr_ctrl_seg) / 16;
	if (unlikely((*seg == qp->sq.qend)))
		*seg = mlx5_get_send_wqe(qp, 0);

	set_reg_mkey_seg(*seg, mr, wr->key, wr->access);
	*seg += sizeof(struct mlx5_mkey_seg);
	*size += sizeof(struct mlx5_mkey_seg) / 16;
	if (unlikely((*seg == qp->sq.qend)))
		*seg = mlx5_get_send_wqe(qp, 0);

	set_reg_data_seg(*seg, mr, pd);
	*seg += sizeof(struct mlx5_wqe_data_seg);
	*size += (sizeof(struct mlx5_wqe_data_seg) / 16);

	return 0;
}