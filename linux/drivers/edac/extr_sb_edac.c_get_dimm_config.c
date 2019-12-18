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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  mcmtr; int /*<<< orphan*/  (* get_node_id ) (struct sbridge_pvt*) ;} ;
struct sbridge_pvt {int is_cur_addr_mirrored; int is_lockstep; int is_close_pg; TYPE_2__ info; int /*<<< orphan*/  pci_ta; void* mirror_mode; int /*<<< orphan*/  pci_ras; scalar_t__ is_chan_hash; int /*<<< orphan*/  pci_ha; TYPE_1__* sbridge_dev; } ;
struct mem_ctl_info {struct sbridge_pvt* pvt_info; } ;
typedef  enum edac_type { ____Placeholder_edac_type } edac_type ;
struct TYPE_3__ {int /*<<< orphan*/  source_id; int /*<<< orphan*/  node_id; int /*<<< orphan*/  mc; } ;

/* Variables and functions */
 void* ADDR_RANGE_MIRRORING ; 
 scalar_t__ BROADWELL ; 
 int EDAC_S4ECD4ED ; 
 int EDAC_S8ECD8ED ; 
 int ENODEV ; 
 void* FULL_MIRRORING ; 
 scalar_t__ GET_BITFIELD (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ HASWELL ; 
 int /*<<< orphan*/  HASWELL_HASYSDEFEATURE2 ; 
 scalar_t__ IS_CLOSE_PG (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_LOCKSTEP_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_MIRROR_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ KNIGHTS_LANDING ; 
 int KNL_MAX_CHANNELS ; 
 int /*<<< orphan*/  KNL_MCMTR ; 
 int /*<<< orphan*/  MCMTR ; 
 void* NON_MIRRORING ; 
 int /*<<< orphan*/  RASENABLES ; 
 int __populate_dimms (struct mem_ctl_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ knl_get_dimm_capacity (struct sbridge_pvt*,int /*<<< orphan*/ *) ; 
 scalar_t__ pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sbridge_pvt*) ; 

__attribute__((used)) static int get_dimm_config(struct mem_ctl_info *mci)
{
	struct sbridge_pvt *pvt = mci->pvt_info;
	u64 knl_mc_sizes[KNL_MAX_CHANNELS];
	enum edac_type mode;
	u32 reg;

	pvt->sbridge_dev->node_id = pvt->info.get_node_id(pvt);
	edac_dbg(0, "mc#%d: Node ID: %d, source ID: %d\n",
		 pvt->sbridge_dev->mc,
		 pvt->sbridge_dev->node_id,
		 pvt->sbridge_dev->source_id);

	/* KNL doesn't support mirroring or lockstep,
	 * and is always closed page
	 */
	if (pvt->info.type == KNIGHTS_LANDING) {
		mode = EDAC_S4ECD4ED;
		pvt->mirror_mode = NON_MIRRORING;
		pvt->is_cur_addr_mirrored = false;

		if (knl_get_dimm_capacity(pvt, knl_mc_sizes) != 0)
			return -1;
		if (pci_read_config_dword(pvt->pci_ta, KNL_MCMTR, &pvt->info.mcmtr)) {
			edac_dbg(0, "Failed to read KNL_MCMTR register\n");
			return -ENODEV;
		}
	} else {
		if (pvt->info.type == HASWELL || pvt->info.type == BROADWELL) {
			if (pci_read_config_dword(pvt->pci_ha, HASWELL_HASYSDEFEATURE2, &reg)) {
				edac_dbg(0, "Failed to read HASWELL_HASYSDEFEATURE2 register\n");
				return -ENODEV;
			}
			pvt->is_chan_hash = GET_BITFIELD(reg, 21, 21);
			if (GET_BITFIELD(reg, 28, 28)) {
				pvt->mirror_mode = ADDR_RANGE_MIRRORING;
				edac_dbg(0, "Address range partial memory mirroring is enabled\n");
				goto next;
			}
		}
		if (pci_read_config_dword(pvt->pci_ras, RASENABLES, &reg)) {
			edac_dbg(0, "Failed to read RASENABLES register\n");
			return -ENODEV;
		}
		if (IS_MIRROR_ENABLED(reg)) {
			pvt->mirror_mode = FULL_MIRRORING;
			edac_dbg(0, "Full memory mirroring is enabled\n");
		} else {
			pvt->mirror_mode = NON_MIRRORING;
			edac_dbg(0, "Memory mirroring is disabled\n");
		}

next:
		if (pci_read_config_dword(pvt->pci_ta, MCMTR, &pvt->info.mcmtr)) {
			edac_dbg(0, "Failed to read MCMTR register\n");
			return -ENODEV;
		}
		if (IS_LOCKSTEP_ENABLED(pvt->info.mcmtr)) {
			edac_dbg(0, "Lockstep is enabled\n");
			mode = EDAC_S8ECD8ED;
			pvt->is_lockstep = true;
		} else {
			edac_dbg(0, "Lockstep is disabled\n");
			mode = EDAC_S4ECD4ED;
			pvt->is_lockstep = false;
		}
		if (IS_CLOSE_PG(pvt->info.mcmtr)) {
			edac_dbg(0, "address map is on closed page mode\n");
			pvt->is_close_pg = true;
		} else {
			edac_dbg(0, "address map is on open page mode\n");
			pvt->is_close_pg = false;
		}
	}

	return __populate_dimms(mci, knl_mc_sizes, mode);
}