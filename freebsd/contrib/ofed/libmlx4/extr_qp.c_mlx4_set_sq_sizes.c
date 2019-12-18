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
struct mlx4_wqe_raddr_seg {int dummy; } ;
struct mlx4_wqe_inline_seg {int dummy; } ;
struct mlx4_wqe_datagram_seg {int dummy; } ;
struct mlx4_wqe_data_seg {int dummy; } ;
struct mlx4_wqe_ctrl_seg {int dummy; } ;
struct TYPE_2__ {int wqe_shift; int max_gs; scalar_t__ max_post; scalar_t__ wqe_cnt; } ;
struct mlx4_qp {int max_inline_data; TYPE_1__ sq; scalar_t__ sq_spare_wqes; } ;
struct ibv_qp_cap {int max_send_sge; int max_inline_data; scalar_t__ max_send_wr; } ;
typedef  enum ibv_qp_type { ____Placeholder_ibv_qp_type } ibv_qp_type ;

/* Variables and functions */
#define  IBV_QPT_RC 131 
#define  IBV_QPT_UC 130 
#define  IBV_QPT_UD 129 
#define  IBV_QPT_XRC_SEND 128 
 int MLX4_INLINE_ALIGN ; 
 int align (int,int) ; 

void mlx4_set_sq_sizes(struct mlx4_qp *qp, struct ibv_qp_cap *cap,
		       enum ibv_qp_type type)
{
	int wqe_size;

	wqe_size = (1 << qp->sq.wqe_shift) - sizeof (struct mlx4_wqe_ctrl_seg);
	switch (type) {
	case IBV_QPT_UD:
		wqe_size -= sizeof (struct mlx4_wqe_datagram_seg);
		break;

	case IBV_QPT_XRC_SEND:
	case IBV_QPT_UC:
	case IBV_QPT_RC:
		wqe_size -= sizeof (struct mlx4_wqe_raddr_seg);
		break;

	default:
		break;
	}

	qp->sq.max_gs	     = wqe_size / sizeof (struct mlx4_wqe_data_seg);
	cap->max_send_sge    = qp->sq.max_gs;
	qp->sq.max_post	     = qp->sq.wqe_cnt - qp->sq_spare_wqes;
	cap->max_send_wr     = qp->sq.max_post;

	/*
	 * Inline data segments can't cross a 64 byte boundary.  So
	 * subtract off one segment header for each 64-byte chunk,
	 * taking into account the fact that wqe_size will be 32 mod
	 * 64 for non-UD QPs.
	 */
	qp->max_inline_data  = wqe_size -
		sizeof (struct mlx4_wqe_inline_seg) *
		(align(wqe_size, MLX4_INLINE_ALIGN) / MLX4_INLINE_ALIGN);
	cap->max_inline_data = qp->max_inline_data;
}