#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mps_softc {TYPE_1__* sassc; } ;
struct TYPE_2__ {int /*<<< orphan*/  mpssas_eh; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPI2_EVENT_IR_CONFIGURATION_CHANGE_LIST ; 
 int /*<<< orphan*/  MPI2_EVENT_IR_OPERATION_STATUS ; 
 int /*<<< orphan*/  MPI2_EVENT_IR_PHYSICAL_DISK ; 
 int /*<<< orphan*/  MPI2_EVENT_IR_VOLUME ; 
 int /*<<< orphan*/  MPI2_EVENT_LOG_ENTRY_ADDED ; 
 int MPI2_EVENT_NOTIFY_EVENTMASK_WORDS ; 
 int /*<<< orphan*/  MPI2_EVENT_SAS_BROADCAST_PRIMITIVE ; 
 int /*<<< orphan*/  MPI2_EVENT_SAS_DEVICE_STATUS_CHANGE ; 
 int /*<<< orphan*/  MPI2_EVENT_SAS_DISCOVERY ; 
 int /*<<< orphan*/  MPI2_EVENT_SAS_ENCL_DEVICE_STATUS_CHANGE ; 
 int /*<<< orphan*/  MPI2_EVENT_SAS_INIT_DEVICE_STATUS_CHANGE ; 
 int /*<<< orphan*/  MPI2_EVENT_SAS_INIT_TABLE_OVERFLOW ; 
 int /*<<< orphan*/  MPI2_EVENT_SAS_TOPOLOGY_CHANGE_LIST ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mps_register_events (struct mps_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpssas_evt_handler ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpssas_register_events(struct mps_softc *sc)
{
	u32 events[MPI2_EVENT_NOTIFY_EVENTMASK_WORDS];

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
	setbit(events, MPI2_EVENT_LOG_ENTRY_ADDED);

	mps_register_events(sc, events, mpssas_evt_handler, NULL,
	    &sc->sassc->mpssas_eh);

	return (0);
}