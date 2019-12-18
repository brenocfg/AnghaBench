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
struct _map_topology_change {int num_entries; struct _map_phy_change* phy_details; int /*<<< orphan*/  exp_status; int /*<<< orphan*/  num_phys; int /*<<< orphan*/  start_phy_num; void* exp_handle; void* enc_handle; } ;
struct _map_phy_change {int reason; void* dev_handle; } ;
struct TYPE_5__ {int NumEntries; TYPE_1__* PHY; int /*<<< orphan*/  ExpStatus; int /*<<< orphan*/  NumPhys; int /*<<< orphan*/  StartPhyNum; int /*<<< orphan*/  ExpanderDevHandle; int /*<<< orphan*/  EnclosureHandle; } ;
struct TYPE_4__ {int PhyStatus; int /*<<< orphan*/  AttachedDevHandle; } ;
typedef  TYPE_1__ Mpi2EventSasTopoPhyEntry_t ;
typedef  TYPE_2__ Mpi2EventDataSasTopologyChangeList_t ;

/* Variables and functions */
 int MPI2_EVENT_SAS_TOPO_RC_MASK ; 
 int /*<<< orphan*/  M_MPR ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  _mapping_add_new_device (struct mpr_softc*,struct _map_topology_change*) ; 
 int /*<<< orphan*/  _mapping_clear_removed_entries (struct mpr_softc*) ; 
 int /*<<< orphan*/  _mapping_flush_dpm_pages (struct mpr_softc*) ; 
 int /*<<< orphan*/  _mapping_get_dev_info (struct mpr_softc*,struct _map_topology_change*) ; 
 int /*<<< orphan*/  _mapping_update_missing_count (struct mpr_softc*,struct _map_topology_change*) ; 
 int /*<<< orphan*/  free (struct _map_phy_change*,int /*<<< orphan*/ ) ; 
 void* le16toh (int /*<<< orphan*/ ) ; 
 struct _map_phy_change* malloc (int,int /*<<< orphan*/ ,int) ; 

void
mpr_mapping_topology_change_event(struct mpr_softc *sc,
    Mpi2EventDataSasTopologyChangeList_t *event_data)
{
	struct _map_topology_change topo_change;
	struct _map_phy_change *phy_change;
	Mpi2EventSasTopoPhyEntry_t *event_phy_change;
	u8 i, num_entries;

	topo_change.enc_handle = le16toh(event_data->EnclosureHandle);
	topo_change.exp_handle = le16toh(event_data->ExpanderDevHandle);
	num_entries = event_data->NumEntries;
	topo_change.num_entries = num_entries;
	topo_change.start_phy_num = event_data->StartPhyNum;
	topo_change.num_phys = event_data->NumPhys;
	topo_change.exp_status = event_data->ExpStatus;
	event_phy_change = event_data->PHY;
	topo_change.phy_details = NULL;

	if (!num_entries)
		goto out;
	phy_change = malloc(sizeof(struct _map_phy_change) * num_entries,
	    M_MPR, M_NOWAIT|M_ZERO);
	topo_change.phy_details = phy_change;
	if (!phy_change)
		goto out;
	for (i = 0; i < num_entries; i++, event_phy_change++, phy_change++) {
		phy_change->dev_handle = le16toh(event_phy_change->
		    AttachedDevHandle);
		phy_change->reason = event_phy_change->PhyStatus &
		    MPI2_EVENT_SAS_TOPO_RC_MASK;
	}
	_mapping_update_missing_count(sc, &topo_change);
	_mapping_get_dev_info(sc, &topo_change);
	_mapping_clear_removed_entries(sc);
	_mapping_add_new_device(sc, &topo_change);

out:
	free(topo_change.phy_details, M_MPR);
	_mapping_flush_dpm_pages(sc);
	if (sc->pending_map_events)
		sc->pending_map_events--;
}