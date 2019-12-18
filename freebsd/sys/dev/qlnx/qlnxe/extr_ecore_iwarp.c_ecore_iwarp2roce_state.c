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
#define  ECORE_IWARP_QP_STATE_CLOSING 132 
#define  ECORE_IWARP_QP_STATE_ERROR 131 
#define  ECORE_IWARP_QP_STATE_IDLE 130 
#define  ECORE_IWARP_QP_STATE_RTS 129 
#define  ECORE_IWARP_QP_STATE_TERMINATE 128 
 int ECORE_ROCE_QP_STATE_ERR ; 
 int ECORE_ROCE_QP_STATE_INIT ; 
 int ECORE_ROCE_QP_STATE_RTS ; 
 int ECORE_ROCE_QP_STATE_SQD ; 
 int ECORE_ROCE_QP_STATE_SQE ; 

__attribute__((used)) static enum ecore_roce_qp_state
ecore_iwarp2roce_state(enum ecore_iwarp_qp_state state)
{
	switch (state) {
	case ECORE_IWARP_QP_STATE_IDLE:
		return ECORE_ROCE_QP_STATE_INIT;
	case ECORE_IWARP_QP_STATE_RTS:
		return ECORE_ROCE_QP_STATE_RTS;
	case ECORE_IWARP_QP_STATE_TERMINATE:
		return ECORE_ROCE_QP_STATE_SQE;
	case ECORE_IWARP_QP_STATE_CLOSING:
		return ECORE_ROCE_QP_STATE_SQD;
	case ECORE_IWARP_QP_STATE_ERROR:
		return ECORE_ROCE_QP_STATE_ERR;
	}
	return ECORE_ROCE_QP_STATE_ERR;
}