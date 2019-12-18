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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int (* get_ha ) (int) ;} ;
struct sbridge_pvt {scalar_t__ mirror_mode; int is_cur_addr_mirrored; scalar_t__ is_lockstep; struct pci_dev* pci_ha; TYPE_1__ info; } ;
struct pci_dev {int dummy; } ;
struct mem_ctl_info {struct sbridge_pvt* pvt_info; } ;
struct mce {int bank; int socketid; scalar_t__ addr; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 scalar_t__ ADDR_RANGE_MIRRORING ; 
 int EINVAL ; 
 scalar_t__ FULL_MIRRORING ; 
 int GET_BITFIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int NUM_CHANNELS ; 
 scalar_t__ TAD_LIMIT (int) ; 
 struct mem_ctl_info* get_mci_for_node_id (int,int) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int stub1 (int) ; 
 int /*<<< orphan*/ * tad_dram_rule ; 

__attribute__((used)) static int get_memory_error_data_from_mce(struct mem_ctl_info *mci,
					  const struct mce *m, u8 *socket,
					  u8 *ha, long *channel_mask,
					  char *msg)
{
	u32 reg, channel = GET_BITFIELD(m->status, 0, 3);
	struct mem_ctl_info *new_mci;
	struct sbridge_pvt *pvt;
	struct pci_dev *pci_ha;
	bool tad0;

	if (channel >= NUM_CHANNELS) {
		sprintf(msg, "Invalid channel 0x%x", channel);
		return -EINVAL;
	}

	pvt = mci->pvt_info;
	if (!pvt->info.get_ha) {
		sprintf(msg, "No get_ha()");
		return -EINVAL;
	}
	*ha = pvt->info.get_ha(m->bank);
	if (*ha != 0 && *ha != 1) {
		sprintf(msg, "Impossible bank %d", m->bank);
		return -EINVAL;
	}

	*socket = m->socketid;
	new_mci = get_mci_for_node_id(*socket, *ha);
	if (!new_mci) {
		strcpy(msg, "mci socket got corrupted!");
		return -EINVAL;
	}

	pvt = new_mci->pvt_info;
	pci_ha = pvt->pci_ha;
	pci_read_config_dword(pci_ha, tad_dram_rule[0], &reg);
	tad0 = m->addr <= TAD_LIMIT(reg);

	*channel_mask = 1 << channel;
	if (pvt->mirror_mode == FULL_MIRRORING ||
	    (pvt->mirror_mode == ADDR_RANGE_MIRRORING && tad0)) {
		*channel_mask |= 1 << ((channel + 2) % 4);
		pvt->is_cur_addr_mirrored = true;
	} else {
		pvt->is_cur_addr_mirrored = false;
	}

	if (pvt->is_lockstep)
		*channel_mask |= 1 << ((channel + 1) % 4);

	return 0;
}