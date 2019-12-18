#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int async_type; } ;
struct TYPE_7__ {TYPE_1__ s; } ;
struct oce_mq_cqe {TYPE_2__ u0; } ;
struct oce_async_evt_grp5_os2bmc {int dummy; } ;
struct oce_async_event_grp5_pvid_state {int tag; int /*<<< orphan*/  enabled; } ;
struct TYPE_8__ {int pvid; } ;
typedef  TYPE_3__* POCE_SOFTC ;

/* Variables and functions */
#define  ASYNC_EVENT_OS2BMC 129 
#define  ASYNC_EVENT_PVID_STATE 128 
 int VLAN_VID_MASK ; 
 int /*<<< orphan*/  oce_async_grp5_osbmc_process (TYPE_3__*,struct oce_async_evt_grp5_os2bmc*) ; 

__attribute__((used)) static void oce_process_grp5_events(POCE_SOFTC sc, struct oce_mq_cqe *cqe)
{
	struct oce_async_event_grp5_pvid_state *gcqe;
	struct oce_async_evt_grp5_os2bmc *bmccqe;

	switch (cqe->u0.s.async_type) {
	case ASYNC_EVENT_PVID_STATE:
		/* GRP5 PVID */
		gcqe = (struct oce_async_event_grp5_pvid_state *)cqe;
		if (gcqe->enabled)
			sc->pvid = gcqe->tag & VLAN_VID_MASK;
		else
			sc->pvid = 0;
		break;
	case ASYNC_EVENT_OS2BMC:
		bmccqe = (struct oce_async_evt_grp5_os2bmc *)cqe;
		oce_async_grp5_osbmc_process(sc, bmccqe);
		break;
	default:
		break;
	}
}