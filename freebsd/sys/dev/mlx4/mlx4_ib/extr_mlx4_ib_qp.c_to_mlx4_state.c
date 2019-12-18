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
typedef  enum mlx4_qp_state { ____Placeholder_mlx4_qp_state } mlx4_qp_state ;
typedef  enum ib_qp_state { ____Placeholder_ib_qp_state } ib_qp_state ;

/* Variables and functions */
#define  IB_QPS_ERR 134 
#define  IB_QPS_INIT 133 
#define  IB_QPS_RESET 132 
#define  IB_QPS_RTR 131 
#define  IB_QPS_RTS 130 
#define  IB_QPS_SQD 129 
#define  IB_QPS_SQE 128 
 int MLX4_QP_STATE_ERR ; 
 int MLX4_QP_STATE_INIT ; 
 int MLX4_QP_STATE_RST ; 
 int MLX4_QP_STATE_RTR ; 
 int MLX4_QP_STATE_RTS ; 
 int MLX4_QP_STATE_SQD ; 
 int MLX4_QP_STATE_SQER ; 

__attribute__((used)) static enum mlx4_qp_state to_mlx4_state(enum ib_qp_state state)
{
	switch (state) {
	case IB_QPS_RESET:	return MLX4_QP_STATE_RST;
	case IB_QPS_INIT:	return MLX4_QP_STATE_INIT;
	case IB_QPS_RTR:	return MLX4_QP_STATE_RTR;
	case IB_QPS_RTS:	return MLX4_QP_STATE_RTS;
	case IB_QPS_SQD:	return MLX4_QP_STATE_SQD;
	case IB_QPS_SQE:	return MLX4_QP_STATE_SQER;
	case IB_QPS_ERR:	return MLX4_QP_STATE_ERR;
	default:		return -1;
	}
}