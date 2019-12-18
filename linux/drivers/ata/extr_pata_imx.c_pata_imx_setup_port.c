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
struct ata_ioports {scalar_t__ cmd_addr; scalar_t__ command_addr; scalar_t__ status_addr; scalar_t__ device_addr; scalar_t__ lbah_addr; scalar_t__ lbam_addr; scalar_t__ lbal_addr; scalar_t__ nsect_addr; scalar_t__ feature_addr; scalar_t__ error_addr; scalar_t__ data_addr; } ;

/* Variables and functions */
 int ATA_REG_CMD ; 
 int ATA_REG_DATA ; 
 int ATA_REG_DEVICE ; 
 int ATA_REG_ERR ; 
 int ATA_REG_FEATURE ; 
 int ATA_REG_LBAH ; 
 int ATA_REG_LBAL ; 
 int ATA_REG_LBAM ; 
 int ATA_REG_NSECT ; 
 int ATA_REG_STATUS ; 

__attribute__((used)) static void pata_imx_setup_port(struct ata_ioports *ioaddr)
{
	/* Fixup the port shift for platforms that need it */
	ioaddr->data_addr	= ioaddr->cmd_addr + (ATA_REG_DATA    << 2);
	ioaddr->error_addr	= ioaddr->cmd_addr + (ATA_REG_ERR     << 2);
	ioaddr->feature_addr	= ioaddr->cmd_addr + (ATA_REG_FEATURE << 2);
	ioaddr->nsect_addr	= ioaddr->cmd_addr + (ATA_REG_NSECT   << 2);
	ioaddr->lbal_addr	= ioaddr->cmd_addr + (ATA_REG_LBAL    << 2);
	ioaddr->lbam_addr	= ioaddr->cmd_addr + (ATA_REG_LBAM    << 2);
	ioaddr->lbah_addr	= ioaddr->cmd_addr + (ATA_REG_LBAH    << 2);
	ioaddr->device_addr	= ioaddr->cmd_addr + (ATA_REG_DEVICE  << 2);
	ioaddr->status_addr	= ioaddr->cmd_addr + (ATA_REG_STATUS  << 2);
	ioaddr->command_addr	= ioaddr->cmd_addr + (ATA_REG_CMD     << 2);
}