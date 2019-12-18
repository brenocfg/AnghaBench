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
struct mlx5_wqe_xrc_seg {int dummy; } ;
struct mlx5_wqe_umr_ctrl_seg {int dummy; } ;
struct mlx5_wqe_raddr_seg {int dummy; } ;
struct mlx5_wqe_eth_seg {int dummy; } ;
struct mlx5_wqe_eth_pad {int dummy; } ;
struct mlx5_wqe_datagram_seg {int dummy; } ;
struct mlx5_wqe_ctrl_seg {int dummy; } ;
struct mlx5_wqe_atomic_seg {int dummy; } ;
struct mlx5_mkey_seg {int dummy; } ;
struct ib_qp_init_attr {int qp_type; int create_flags; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IB_QPT_RC 135 
#define  IB_QPT_SMI 134 
#define  IB_QPT_UC 133 
#define  IB_QPT_UD 132 
#define  IB_QPT_XRC_INI 131 
#define  IB_QPT_XRC_TGT 130 
 int IB_QP_CREATE_IPOIB_UD_LSO ; 
#define  MLX5_IB_QPT_HW_GSI 129 
#define  MLX5_IB_QPT_REG_UMR 128 
 int /*<<< orphan*/  max (int,int) ; 

__attribute__((used)) static int sq_overhead(struct ib_qp_init_attr *attr)
{
	int size = 0;

	switch (attr->qp_type) {
	case IB_QPT_XRC_INI:
		size += sizeof(struct mlx5_wqe_xrc_seg);
		/* fall through */
	case IB_QPT_RC:
		size += sizeof(struct mlx5_wqe_ctrl_seg) +
			max(sizeof(struct mlx5_wqe_atomic_seg) +
			    sizeof(struct mlx5_wqe_raddr_seg),
			    sizeof(struct mlx5_wqe_umr_ctrl_seg) +
			    sizeof(struct mlx5_mkey_seg));
		break;

	case IB_QPT_XRC_TGT:
		return 0;

	case IB_QPT_UC:
		size += sizeof(struct mlx5_wqe_ctrl_seg) +
			max(sizeof(struct mlx5_wqe_raddr_seg),
			    sizeof(struct mlx5_wqe_umr_ctrl_seg) +
			    sizeof(struct mlx5_mkey_seg));
		break;

	case IB_QPT_UD:
		if (attr->create_flags & IB_QP_CREATE_IPOIB_UD_LSO)
			size += sizeof(struct mlx5_wqe_eth_pad) +
				sizeof(struct mlx5_wqe_eth_seg);
		/* fall through */
	case IB_QPT_SMI:
	case MLX5_IB_QPT_HW_GSI:
		size += sizeof(struct mlx5_wqe_ctrl_seg) +
			sizeof(struct mlx5_wqe_datagram_seg);
		break;

	case MLX5_IB_QPT_REG_UMR:
		size += sizeof(struct mlx5_wqe_ctrl_seg) +
			sizeof(struct mlx5_wqe_umr_ctrl_seg) +
			sizeof(struct mlx5_mkey_seg);
		break;

	default:
		return -EINVAL;
	}

	return size;
}