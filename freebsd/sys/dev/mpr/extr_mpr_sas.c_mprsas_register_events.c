#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct mpr_softc {int mpr_flags; TYPE_2__* sassc; TYPE_1__* facts; } ;
struct TYPE_4__ {int /*<<< orphan*/  mprsas_eh; } ;
struct TYPE_3__ {scalar_t__ MsgVersion; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPI2_EVENT_ACTIVE_CABLE_EXCEPTION ; 
 int /*<<< orphan*/  MPI2_EVENT_IR_CONFIGURATION_CHANGE_LIST ; 
 int /*<<< orphan*/  MPI2_EVENT_IR_OPERATION_STATUS ; 
 int /*<<< orphan*/  MPI2_EVENT_IR_PHYSICAL_DISK ; 
 int /*<<< orphan*/  MPI2_EVENT_IR_VOLUME ; 
 int /*<<< orphan*/  MPI2_EVENT_PCIE_DEVICE_STATUS_CHANGE ; 
 int /*<<< orphan*/  MPI2_EVENT_PCIE_ENUMERATION ; 
 int /*<<< orphan*/  MPI2_EVENT_PCIE_TOPOLOGY_CHANGE_LIST ; 
 int /*<<< orphan*/  MPI2_EVENT_SAS_BROADCAST_PRIMITIVE ; 
 int /*<<< orphan*/  MPI2_EVENT_SAS_DEVICE_DISCOVERY_ERROR ; 
 int /*<<< orphan*/  MPI2_EVENT_SAS_DEVICE_STATUS_CHANGE ; 
 int /*<<< orphan*/  MPI2_EVENT_SAS_DISCOVERY ; 
 int /*<<< orphan*/  MPI2_EVENT_SAS_ENCL_DEVICE_STATUS_CHANGE ; 
 int /*<<< orphan*/  MPI2_EVENT_SAS_INIT_DEVICE_STATUS_CHANGE ; 
 int /*<<< orphan*/  MPI2_EVENT_SAS_INIT_TABLE_OVERFLOW ; 
 int /*<<< orphan*/  MPI2_EVENT_SAS_TOPOLOGY_CHANGE_LIST ; 
 int /*<<< orphan*/  MPI2_EVENT_TEMP_THRESHOLD ; 
 scalar_t__ MPI2_VERSION_02_06 ; 
 int MPR_FLAGS_GEN35_IOC ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mpr_register_events (struct mpr_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mprsas_evt_handler ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mprsas_register_events(struct mpr_softc *sc)
{
	uint8_t events[16];

	bzero(events, 16);
	setbit(events, MPI2_EVENT_SAS_DEVICE_STATUS_CHANGE);
	setbit(events, MPI2_EVENT_SAS_DISCOVERY);
	setbit(events, MPI2_EVENT_SAS_BROADCAST_PRIMITIVE);
	setbit(events, MPI2_EVENT_SAS_INIT_DEVICE_STATUS_CHANGE);
	setbit(events, MPI2_EVENT_SAS_INIT_TABLE_OVERFLOW);
	setbit(events, MPI2_EVENT_SAS_TOPOLOGY_CHANGE_LIST);
	setbit(events, MPI2_EVENT_SAS_ENCL_DEVICE_STATUS_CHANGE);
	setbit(events, MPI2_EVENT_IR_CONFIGURATION_CHANGE_LIST);
	setbit(events, MPI2_EVENT_IR_VOLUME);
	setbit(events, MPI2_EVENT_IR_PHYSICAL_DISK);
	setbit(events, MPI2_EVENT_IR_OPERATION_STATUS);
	setbit(events, MPI2_EVENT_TEMP_THRESHOLD);
	setbit(events, MPI2_EVENT_SAS_DEVICE_DISCOVERY_ERROR);
	if (sc->facts->MsgVersion >= MPI2_VERSION_02_06) {
		setbit(events, MPI2_EVENT_ACTIVE_CABLE_EXCEPTION);
		if (sc->mpr_flags & MPR_FLAGS_GEN35_IOC) {
			setbit(events, MPI2_EVENT_PCIE_DEVICE_STATUS_CHANGE);
			setbit(events, MPI2_EVENT_PCIE_ENUMERATION);
			setbit(events, MPI2_EVENT_PCIE_TOPOLOGY_CHANGE_LIST);
		}
	}

	mpr_register_events(sc, events, mprsas_evt_handler, NULL,
	    &sc->sassc->mprsas_eh);

	return (0);
}