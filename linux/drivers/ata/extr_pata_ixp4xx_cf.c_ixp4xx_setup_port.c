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
struct ixp4xx_pata_data {scalar_t__ cs1; int /*<<< orphan*/  cs0; } ;
struct ata_ioports {int /*<<< orphan*/  command_addr; int /*<<< orphan*/  status_addr; int /*<<< orphan*/  device_addr; int /*<<< orphan*/  lbah_addr; int /*<<< orphan*/  lbam_addr; int /*<<< orphan*/  lbal_addr; int /*<<< orphan*/  nsect_addr; int /*<<< orphan*/  feature_addr; int /*<<< orphan*/  error_addr; scalar_t__ ctl_addr; scalar_t__ altstatus_addr; int /*<<< orphan*/  cmd_addr; int /*<<< orphan*/  data_addr; } ;
struct ata_port {struct ata_ioports ioaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_port_desc (struct ata_port*,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ata_sff_std_ports (struct ata_ioports*) ; 

__attribute__((used)) static void ixp4xx_setup_port(struct ata_port *ap,
			      struct ixp4xx_pata_data *data,
			      unsigned long raw_cs0, unsigned long raw_cs1)
{
	struct ata_ioports *ioaddr = &ap->ioaddr;
	unsigned long raw_cmd = raw_cs0;
	unsigned long raw_ctl = raw_cs1 + 0x06;

	ioaddr->cmd_addr	= data->cs0;
	ioaddr->altstatus_addr	= data->cs1 + 0x06;
	ioaddr->ctl_addr	= data->cs1 + 0x06;

	ata_sff_std_ports(ioaddr);

#ifndef __ARMEB__

	/* adjust the addresses to handle the address swizzling of the
	 * ixp4xx in little endian mode.
	 */

	*(unsigned long *)&ioaddr->data_addr		^= 0x02;
	*(unsigned long *)&ioaddr->cmd_addr		^= 0x03;
	*(unsigned long *)&ioaddr->altstatus_addr	^= 0x03;
	*(unsigned long *)&ioaddr->ctl_addr		^= 0x03;
	*(unsigned long *)&ioaddr->error_addr		^= 0x03;
	*(unsigned long *)&ioaddr->feature_addr		^= 0x03;
	*(unsigned long *)&ioaddr->nsect_addr		^= 0x03;
	*(unsigned long *)&ioaddr->lbal_addr		^= 0x03;
	*(unsigned long *)&ioaddr->lbam_addr		^= 0x03;
	*(unsigned long *)&ioaddr->lbah_addr		^= 0x03;
	*(unsigned long *)&ioaddr->device_addr		^= 0x03;
	*(unsigned long *)&ioaddr->status_addr		^= 0x03;
	*(unsigned long *)&ioaddr->command_addr		^= 0x03;

	raw_cmd ^= 0x03;
	raw_ctl ^= 0x03;
#endif

	ata_port_desc(ap, "cmd 0x%lx ctl 0x%lx", raw_cmd, raw_ctl);
}