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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct pci_dev {int dummy; } ;
struct TYPE_4__ {scalar_t__ num; } ;
struct TYPE_3__ {struct pci_dev* link; } ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_2__ amd_northbridges ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* node_to_amd_nb (scalar_t__) ; 
 int pci_read_config_dword (struct pci_dev*,int,scalar_t__*) ; 
 int pci_write_config_dword (struct pci_dev*,int,scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__) ; 
 int /*<<< orphan*/  smn_mutex ; 

int amd_df_indirect_read(u16 node, u8 func, u16 reg, u8 instance_id, u32 *lo)
{
	struct pci_dev *F4;
	u32 ficaa;
	int err = -ENODEV;

	if (node >= amd_northbridges.num)
		goto out;

	F4 = node_to_amd_nb(node)->link;
	if (!F4)
		goto out;

	ficaa  = 1;
	ficaa |= reg & 0x3FC;
	ficaa |= (func & 0x7) << 11;
	ficaa |= instance_id << 16;

	mutex_lock(&smn_mutex);

	err = pci_write_config_dword(F4, 0x5C, ficaa);
	if (err) {
		pr_warn("Error writing DF Indirect FICAA, FICAA=0x%x\n", ficaa);
		goto out_unlock;
	}

	err = pci_read_config_dword(F4, 0x98, lo);
	if (err)
		pr_warn("Error reading DF Indirect FICAD LO, FICAA=0x%x.\n", ficaa);

out_unlock:
	mutex_unlock(&smn_mutex);

out:
	return err;
}