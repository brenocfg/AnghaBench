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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  device_addr; } ;
struct ata_port {TYPE_1__ ioaddr; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DEV1 ; 
 int /*<<< orphan*/  ATA_DEVICE_OBS ; 
 int /*<<< orphan*/  ata_outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_sff_pause (struct ata_port*) ; 

__attribute__((used)) static void pata_s3c_dev_select(struct ata_port *ap, unsigned int device)
{
	u8 tmp = ATA_DEVICE_OBS;

	if (device != 0)
		tmp |= ATA_DEV1;

	ata_outb(ap->host, tmp, ap->ioaddr.device_addr);
	ata_sff_pause(ap);
}