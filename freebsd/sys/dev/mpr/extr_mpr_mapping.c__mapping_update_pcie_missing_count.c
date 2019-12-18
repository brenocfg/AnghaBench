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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mpr_softc {int dummy; } ;
struct _map_port_change {scalar_t__ reason; int is_processed; int /*<<< orphan*/  dev_handle; } ;
struct _map_pcie_topology_change {size_t num_entries; struct _map_port_change* port_details; } ;

/* Variables and functions */
 scalar_t__ MPI26_EVENT_PCIE_TOPO_PS_NOT_RESPONDING ; 
 int /*<<< orphan*/  _mapping_get_mt_idx_from_handle (struct mpr_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mapping_inc_missing_count (struct mpr_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_mapping_update_pcie_missing_count(struct mpr_softc *sc,
    struct _map_pcie_topology_change *topo_change)
{
	u8 entry;
	struct _map_port_change *port_change;
	u32 map_idx;

	for (entry = 0; entry < topo_change->num_entries; entry++) {
		port_change = &topo_change->port_details[entry];
		if (!port_change->dev_handle || (port_change->reason !=
		    MPI26_EVENT_PCIE_TOPO_PS_NOT_RESPONDING))
			continue;
		map_idx = _mapping_get_mt_idx_from_handle(sc, port_change->
		    dev_handle);
		port_change->is_processed = 1;
		_mapping_inc_missing_count(sc, map_idx);
	}
}