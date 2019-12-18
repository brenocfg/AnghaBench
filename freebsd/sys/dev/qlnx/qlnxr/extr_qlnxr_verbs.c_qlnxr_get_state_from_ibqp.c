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
 int ECORE_ROCE_QP_STATE_ERR ; 
 int ECORE_ROCE_QP_STATE_INIT ; 
 int ECORE_ROCE_QP_STATE_RESET ; 
 int ECORE_ROCE_QP_STATE_RTR ; 
 int ECORE_ROCE_QP_STATE_RTS ; 
 int ECORE_ROCE_QP_STATE_SQD ; 
#define  IB_QPS_ERR 133 
#define  IB_QPS_INIT 132 
#define  IB_QPS_RESET 131 
#define  IB_QPS_RTR 130 
#define  IB_QPS_RTS 129 
#define  IB_QPS_SQD 128 

__attribute__((used)) static enum ecore_roce_qp_state
qlnxr_get_state_from_ibqp( enum ib_qp_state qp_state)
{
	enum ecore_roce_qp_state ecore_qp_state;

	ecore_qp_state = ECORE_ROCE_QP_STATE_ERR;

	switch (qp_state) {
	case IB_QPS_RESET:
		ecore_qp_state =  ECORE_ROCE_QP_STATE_RESET;
		break;

	case IB_QPS_INIT:
		ecore_qp_state =  ECORE_ROCE_QP_STATE_INIT;
		break;

	case IB_QPS_RTR:
		ecore_qp_state =  ECORE_ROCE_QP_STATE_RTR;
		break;

	case IB_QPS_RTS:
		ecore_qp_state =  ECORE_ROCE_QP_STATE_RTS;
		break;

	case IB_QPS_SQD:
		ecore_qp_state =  ECORE_ROCE_QP_STATE_SQD;
		break;

	case IB_QPS_ERR:
		ecore_qp_state =  ECORE_ROCE_QP_STATE_ERR;
		break;

	default:
		ecore_qp_state =  ECORE_ROCE_QP_STATE_ERR;
		break;
	}

	return (ecore_qp_state);
}