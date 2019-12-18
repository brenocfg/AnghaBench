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
typedef  enum ib_qp_state { ____Placeholder_ib_qp_state } ib_qp_state ;
typedef  enum ecore_roce_qp_state { ____Placeholder_ecore_roce_qp_state } ecore_roce_qp_state ;

/* Variables and functions */
#define  ECORE_ROCE_QP_STATE_ERR 134 
#define  ECORE_ROCE_QP_STATE_INIT 133 
#define  ECORE_ROCE_QP_STATE_RESET 132 
#define  ECORE_ROCE_QP_STATE_RTR 131 
#define  ECORE_ROCE_QP_STATE_RTS 130 
#define  ECORE_ROCE_QP_STATE_SQD 129 
#define  ECORE_ROCE_QP_STATE_SQE 128 
 int IB_QPS_ERR ; 
 int IB_QPS_INIT ; 
 int IB_QPS_RESET ; 
 int IB_QPS_RTR ; 
 int IB_QPS_RTS ; 
 int IB_QPS_SQD ; 
 int IB_QPS_SQE ; 

__attribute__((used)) static enum ib_qp_state
qlnxr_get_ibqp_state(enum ecore_roce_qp_state qp_state)
{
	enum ib_qp_state state = IB_QPS_ERR;

	switch (qp_state) {
	case ECORE_ROCE_QP_STATE_RESET:
		state = IB_QPS_RESET;
		break;

	case ECORE_ROCE_QP_STATE_INIT:
		state = IB_QPS_INIT;
		break;

	case ECORE_ROCE_QP_STATE_RTR:
		state = IB_QPS_RTR;
		break;

	case ECORE_ROCE_QP_STATE_RTS:
		state = IB_QPS_RTS;
		break;

	case ECORE_ROCE_QP_STATE_SQD:
		state = IB_QPS_SQD;
		break;

	case ECORE_ROCE_QP_STATE_ERR:
		state = IB_QPS_ERR;
		break;

	case ECORE_ROCE_QP_STATE_SQE:
		state = IB_QPS_SQE;
		break;
	}
	return state;
}