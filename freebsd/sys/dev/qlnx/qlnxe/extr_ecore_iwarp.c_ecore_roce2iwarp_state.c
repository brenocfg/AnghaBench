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
typedef  enum ecore_roce_qp_state { ____Placeholder_ecore_roce_qp_state } ecore_roce_qp_state ;
typedef  enum ecore_iwarp_qp_state { ____Placeholder_ecore_iwarp_qp_state } ecore_iwarp_qp_state ;

/* Variables and functions */
 int ECORE_IWARP_QP_STATE_CLOSING ; 
 int ECORE_IWARP_QP_STATE_ERROR ; 
 int ECORE_IWARP_QP_STATE_IDLE ; 
 int ECORE_IWARP_QP_STATE_RTS ; 
 int ECORE_IWARP_QP_STATE_TERMINATE ; 
#define  ECORE_ROCE_QP_STATE_ERR 134 
#define  ECORE_ROCE_QP_STATE_INIT 133 
#define  ECORE_ROCE_QP_STATE_RESET 132 
#define  ECORE_ROCE_QP_STATE_RTR 131 
#define  ECORE_ROCE_QP_STATE_RTS 130 
#define  ECORE_ROCE_QP_STATE_SQD 129 
#define  ECORE_ROCE_QP_STATE_SQE 128 

enum ecore_iwarp_qp_state
ecore_roce2iwarp_state(enum ecore_roce_qp_state state)
{
	switch (state) {
	case ECORE_ROCE_QP_STATE_RESET:
	case ECORE_ROCE_QP_STATE_INIT:
	case ECORE_ROCE_QP_STATE_RTR:
		return ECORE_IWARP_QP_STATE_IDLE;
	case ECORE_ROCE_QP_STATE_RTS:
		return ECORE_IWARP_QP_STATE_RTS;
	case ECORE_ROCE_QP_STATE_SQD:
		return ECORE_IWARP_QP_STATE_CLOSING;
	case ECORE_ROCE_QP_STATE_ERR:
		return ECORE_IWARP_QP_STATE_ERROR;
	case ECORE_ROCE_QP_STATE_SQE:
		return ECORE_IWARP_QP_STATE_TERMINATE;
	}
	return ECORE_IWARP_QP_STATE_ERROR;
}