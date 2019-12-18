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
struct mlx5_err_cqe {int syndrome; } ;
typedef  enum ibv_wc_status { ____Placeholder_ibv_wc_status } ibv_wc_status ;

/* Variables and functions */
 int IBV_WC_BAD_RESP_ERR ; 
 int IBV_WC_GENERAL_ERR ; 
 int IBV_WC_LOC_ACCESS_ERR ; 
 int IBV_WC_LOC_LEN_ERR ; 
 int IBV_WC_LOC_PROT_ERR ; 
 int IBV_WC_LOC_QP_OP_ERR ; 
 int IBV_WC_MW_BIND_ERR ; 
 int IBV_WC_REM_ABORT_ERR ; 
 int IBV_WC_REM_ACCESS_ERR ; 
 int IBV_WC_REM_INV_REQ_ERR ; 
 int IBV_WC_REM_OP_ERR ; 
 int IBV_WC_RETRY_EXC_ERR ; 
 int IBV_WC_RNR_RETRY_EXC_ERR ; 
 int IBV_WC_WR_FLUSH_ERR ; 
#define  MLX5_CQE_SYNDROME_BAD_RESP_ERR 140 
#define  MLX5_CQE_SYNDROME_LOCAL_ACCESS_ERR 139 
#define  MLX5_CQE_SYNDROME_LOCAL_LENGTH_ERR 138 
#define  MLX5_CQE_SYNDROME_LOCAL_PROT_ERR 137 
#define  MLX5_CQE_SYNDROME_LOCAL_QP_OP_ERR 136 
#define  MLX5_CQE_SYNDROME_MW_BIND_ERR 135 
#define  MLX5_CQE_SYNDROME_REMOTE_ABORTED_ERR 134 
#define  MLX5_CQE_SYNDROME_REMOTE_ACCESS_ERR 133 
#define  MLX5_CQE_SYNDROME_REMOTE_INVAL_REQ_ERR 132 
#define  MLX5_CQE_SYNDROME_REMOTE_OP_ERR 131 
#define  MLX5_CQE_SYNDROME_RNR_RETRY_EXC_ERR 130 
#define  MLX5_CQE_SYNDROME_TRANSPORT_RETRY_EXC_ERR 129 
#define  MLX5_CQE_SYNDROME_WR_FLUSH_ERR 128 

__attribute__((used)) static enum ibv_wc_status mlx5_handle_error_cqe(struct mlx5_err_cqe *cqe)
{
	switch (cqe->syndrome) {
	case MLX5_CQE_SYNDROME_LOCAL_LENGTH_ERR:
		return IBV_WC_LOC_LEN_ERR;
	case MLX5_CQE_SYNDROME_LOCAL_QP_OP_ERR:
		return IBV_WC_LOC_QP_OP_ERR;
	case MLX5_CQE_SYNDROME_LOCAL_PROT_ERR:
		return IBV_WC_LOC_PROT_ERR;
	case MLX5_CQE_SYNDROME_WR_FLUSH_ERR:
		return IBV_WC_WR_FLUSH_ERR;
	case MLX5_CQE_SYNDROME_MW_BIND_ERR:
		return IBV_WC_MW_BIND_ERR;
	case MLX5_CQE_SYNDROME_BAD_RESP_ERR:
		return IBV_WC_BAD_RESP_ERR;
	case MLX5_CQE_SYNDROME_LOCAL_ACCESS_ERR:
		return IBV_WC_LOC_ACCESS_ERR;
	case MLX5_CQE_SYNDROME_REMOTE_INVAL_REQ_ERR:
		return IBV_WC_REM_INV_REQ_ERR;
	case MLX5_CQE_SYNDROME_REMOTE_ACCESS_ERR:
		return IBV_WC_REM_ACCESS_ERR;
	case MLX5_CQE_SYNDROME_REMOTE_OP_ERR:
		return IBV_WC_REM_OP_ERR;
	case MLX5_CQE_SYNDROME_TRANSPORT_RETRY_EXC_ERR:
		return IBV_WC_RETRY_EXC_ERR;
	case MLX5_CQE_SYNDROME_RNR_RETRY_EXC_ERR:
		return IBV_WC_RNR_RETRY_EXC_ERR;
	case MLX5_CQE_SYNDROME_REMOTE_ABORTED_ERR:
		return IBV_WC_REM_ABORT_ERR;
	default:
		return IBV_WC_GENERAL_ERR;
	}
}