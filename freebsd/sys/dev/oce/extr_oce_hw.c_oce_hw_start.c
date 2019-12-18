#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct link_status {scalar_t__ logical_link_status; scalar_t__ qos_link_speed; int /*<<< orphan*/  phys_port_speed; int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {int qos_link_speed; TYPE_1__** eq; int /*<<< orphan*/  mq; int /*<<< orphan*/  link_speed; int /*<<< orphan*/  ifp; scalar_t__ link_status; } ;
struct TYPE_8__ {int /*<<< orphan*/  eq_id; } ;
typedef  TYPE_2__* POCE_SOFTC ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 scalar_t__ NTWK_LOGICAL_LINK_DOWN ; 
 scalar_t__ NTWK_LOGICAL_LINK_UP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  if_link_state_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oce_arm_eq (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oce_first_mcc_cmd (TYPE_2__*) ; 
 int oce_get_link_status (TYPE_2__*,struct link_status*) ; 
 int /*<<< orphan*/  oce_hw_intr_enable (TYPE_2__*) ; 
 int oce_start_mq (int /*<<< orphan*/ ) ; 

int
oce_hw_start(POCE_SOFTC sc)
{
	struct link_status link = { 0 };
	int rc = 0;

	rc = oce_get_link_status(sc, &link);
	if (rc) 
		return 1;
	
	if (link.logical_link_status == NTWK_LOGICAL_LINK_UP) {
		sc->link_status = NTWK_LOGICAL_LINK_UP;
		if_link_state_change(sc->ifp, LINK_STATE_UP);
	} else {
		sc->link_status = NTWK_LOGICAL_LINK_DOWN;
		if_link_state_change(sc->ifp, LINK_STATE_DOWN);
	}

	sc->link_speed = link.phys_port_speed;
	sc->qos_link_speed = (uint32_t )link.qos_link_speed * 10;

	rc = oce_start_mq(sc->mq);
	
	/* we need to get MCC aync events. So enable intrs and arm
	   first EQ, Other EQs will be armed after interface is UP 
	*/
	oce_hw_intr_enable(sc);
	oce_arm_eq(sc, sc->eq[0]->eq_id, 0, TRUE, FALSE);

	/* Send first mcc cmd and after that we get gracious
	   MCC notifications from FW
	*/
	oce_first_mcc_cmd(sc);

	return rc;
}