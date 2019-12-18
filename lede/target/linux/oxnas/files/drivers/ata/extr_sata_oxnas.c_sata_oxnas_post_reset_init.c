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
typedef  size_t uint ;
struct TYPE_3__ {TYPE_2__* device; } ;
struct ata_port {TYPE_1__ link; int /*<<< orphan*/  port_no; int /*<<< orphan*/  host; } ;
struct TYPE_4__ {scalar_t__ class; } ;

/* Variables and functions */
 scalar_t__ ATA_DEV_ATA ; 
 size_t ATA_MAX_DEVICES ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  SCR_ACTIVE ; 
 int /*<<< orphan*/  SCR_ERROR ; 
 int /*<<< orphan*/  SERROR_IRQ_MASK ; 
 int /*<<< orphan*/  VPRINTK (char*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  sata_oxnas_dev_config (TYPE_2__*) ; 
 int /*<<< orphan*/  sata_oxnas_irq_on (struct ata_port*) ; 
 int /*<<< orphan*/  sata_oxnas_link_write (struct ata_port*,int,int) ; 
 int /*<<< orphan*/  sata_oxnas_reset_ucode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sata_oxnas_scr_write_port (struct ata_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sata_std_hardreset (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void sata_oxnas_post_reset_init(struct ata_port *ap)
{
	uint dev;

	/* force to load u-code only once after reset */
	sata_oxnas_reset_ucode(ap->host, !ap->port_no, 0);

	/* turn on phy error detection by removing the masks */
	sata_oxnas_link_write(ap, 0x0C, 0x30003);

	/* enable hotplug event detection */
	sata_oxnas_scr_write_port(ap, SCR_ERROR, ~0);
	sata_oxnas_scr_write_port(ap, SERROR_IRQ_MASK, 0x03feffff);
	sata_oxnas_scr_write_port(ap, SCR_ACTIVE, ~0 & ~(1 << 26) & ~(1 << 16));

	/* enable interrupts for ports */
	sata_oxnas_irq_on(ap);

	/* go through all the devices and configure them */
	for (dev = 0; dev < ATA_MAX_DEVICES; ++dev) {
		if (ap->link.device[dev].class == ATA_DEV_ATA) {
			sata_std_hardreset(&ap->link, NULL, jiffies + HZ);
			sata_oxnas_dev_config(&(ap->link.device[dev]));
		}
	}

	/* clean up any remaining errors */
	sata_oxnas_scr_write_port(ap, SCR_ERROR, ~0);
	VPRINTK("done\n");
}