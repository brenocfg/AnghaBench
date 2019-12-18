#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct mpr_softc {scalar_t__ pending_map_events; } ;
struct _map_port_change {int /*<<< orphan*/  reason; void* dev_handle; } ;
struct _map_pcie_topology_change {int num_entries; struct _map_port_change* port_details; int /*<<< orphan*/  switch_status; int /*<<< orphan*/  num_ports; int /*<<< orphan*/  start_port_num; void* enc_handle; void* switch_dev_handle; } ;
struct TYPE_5__ {int NumEntries; TYPE_1__* PortEntry; int /*<<< orphan*/  SwitchStatus; int /*<<< orphan*/  NumPorts; int /*<<< orphan*/  StartPortNum; int /*<<< orphan*/  EnclosureHandle; int /*<<< orphan*/  SwitchDevHandle; } ;
struct TYPE_4__ {int /*<<< orphan*/  PortStatus; int /*<<< orphan*/  AttachedDevHandle; } ;
typedef  TYPE_1__ Mpi26EventPCIeTopoPortEntry_t ;
typedef  TYPE_2__ Mpi26EventDataPCIeTopologyChangeList_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_MPR ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  _mapping_add_new_pcie_device (struct mpr_softc*,struct _map_pcie_topology_change*) ; 
 int /*<<< orphan*/  _mapping_clear_removed_entries (struct mpr_softc*) ; 
 int /*<<< orphan*/  _mapping_flush_dpm_pages (struct mpr_softc*) ; 
 int /*<<< orphan*/  _mapping_get_pcie_dev_info (struct mpr_softc*,struct _map_pcie_topology_change*) ; 
 int /*<<< orphan*/  _mapping_update_pcie_missing_count (struct mpr_softc*,struct _map_pcie_topology_change*) ; 
 int /*<<< orphan*/  free (struct _map_port_change*,int /*<<< orphan*/ ) ; 
 void* le16toh (int /*<<< orphan*/ ) ; 
 struct _map_port_change* malloc (int,int /*<<< orphan*/ ,int) ; 

void
mpr_mapping_pcie_topology_change_event(struct mpr_softc *sc,
    Mpi26EventDataPCIeTopologyChangeList_t *event_data)
{
	struct _map_pcie_topology_change topo_change;
	struct _map_port_change *port_change;
	Mpi26EventPCIeTopoPortEntry_t *event_port_change;
	u8 i, num_entries;

	topo_change.switch_dev_handle = le16toh(event_data->SwitchDevHandle);
	topo_change.enc_handle = le16toh(event_data->EnclosureHandle);
	num_entries = event_data->NumEntries;
	topo_change.num_entries = num_entries;
	topo_change.start_port_num = event_data->StartPortNum;
	topo_change.num_ports = event_data->NumPorts;
	topo_change.switch_status = event_data->SwitchStatus;
	event_port_change = event_data->PortEntry;
	topo_change.port_details = NULL;

	if (!num_entries)
		goto out;
	port_change = malloc(sizeof(struct _map_port_change) * num_entries,
	    M_MPR, M_NOWAIT|M_ZERO);
	topo_change.port_details = port_change;
	if (!port_change)
		goto out;
	for (i = 0; i < num_entries; i++, event_port_change++, port_change++) {
		port_change->dev_handle = le16toh(event_port_change->
		    AttachedDevHandle);
		port_change->reason = event_port_change->PortStatus;
	}
	_mapping_update_pcie_missing_count(sc, &topo_change);
	_mapping_get_pcie_dev_info(sc, &topo_change);
	_mapping_clear_removed_entries(sc);
	_mapping_add_new_pcie_device(sc, &topo_change);

out:
	free(topo_change.port_details, M_MPR);
	_mapping_flush_dpm_pages(sc);
	if (sc->pending_map_events)
		sc->pending_map_events--;
}