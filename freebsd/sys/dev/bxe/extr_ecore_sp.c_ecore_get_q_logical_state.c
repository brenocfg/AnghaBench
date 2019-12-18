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
struct ecore_queue_sp_obj {int state; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int ECORE_INVAL ; 
 int ECORE_Q_LOGICAL_STATE_ACTIVE ; 
 int ECORE_Q_LOGICAL_STATE_STOPPED ; 
#define  ECORE_Q_STATE_ACTIVE 136 
#define  ECORE_Q_STATE_FLRED 135 
#define  ECORE_Q_STATE_INACTIVE 134 
#define  ECORE_Q_STATE_INITIALIZED 133 
#define  ECORE_Q_STATE_MCOS_TERMINATED 132 
#define  ECORE_Q_STATE_MULTI_COS 131 
#define  ECORE_Q_STATE_RESET 130 
#define  ECORE_Q_STATE_STOPPED 129 
#define  ECORE_Q_STATE_TERMINATED 128 

int ecore_get_q_logical_state(struct bxe_softc *sc,
			       struct ecore_queue_sp_obj *obj)
{
	switch (obj->state) {
	case ECORE_Q_STATE_ACTIVE:
	case ECORE_Q_STATE_MULTI_COS:
		return ECORE_Q_LOGICAL_STATE_ACTIVE;
	case ECORE_Q_STATE_RESET:
	case ECORE_Q_STATE_INITIALIZED:
	case ECORE_Q_STATE_MCOS_TERMINATED:
	case ECORE_Q_STATE_INACTIVE:
	case ECORE_Q_STATE_STOPPED:
	case ECORE_Q_STATE_TERMINATED:
	case ECORE_Q_STATE_FLRED:
		return ECORE_Q_LOGICAL_STATE_STOPPED;
	default:
		return ECORE_INVAL;
	}
}