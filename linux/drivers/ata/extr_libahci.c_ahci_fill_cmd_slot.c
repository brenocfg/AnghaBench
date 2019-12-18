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
typedef  int u32 ;
struct ahci_port_priv {int cmd_tbl_dma; TYPE_1__* cmd_slot; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {void* tbl_addr_hi; void* tbl_addr; scalar_t__ status; void* opts; } ;

/* Variables and functions */
 unsigned int AHCI_CMD_TBL_SZ ; 
 void* cpu_to_le32 (int) ; 

void ahci_fill_cmd_slot(struct ahci_port_priv *pp, unsigned int tag,
			u32 opts)
{
	dma_addr_t cmd_tbl_dma;

	cmd_tbl_dma = pp->cmd_tbl_dma + tag * AHCI_CMD_TBL_SZ;

	pp->cmd_slot[tag].opts = cpu_to_le32(opts);
	pp->cmd_slot[tag].status = 0;
	pp->cmd_slot[tag].tbl_addr = cpu_to_le32(cmd_tbl_dma & 0xffffffff);
	pp->cmd_slot[tag].tbl_addr_hi = cpu_to_le32((cmd_tbl_dma >> 16) >> 16);
}