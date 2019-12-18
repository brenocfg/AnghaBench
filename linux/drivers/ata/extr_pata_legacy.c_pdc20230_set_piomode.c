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
typedef  int u8 ;
struct ata_port {int dummy; } ;
struct ata_device {int pio_mode; int devno; } ;

/* Variables and functions */
 int XFER_PIO_0 ; 
 int inb (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void pdc20230_set_piomode(struct ata_port *ap, struct ata_device *adev)
{
	int tries = 5;
	int pio = adev->pio_mode - XFER_PIO_0;
	u8 rt;
	unsigned long flags;

	/* Safe as UP only. Force I/Os to occur together */

	local_irq_save(flags);

	/* Unlock the control interface */
	do {
		inb(0x1F5);
		outb(inb(0x1F2) | 0x80, 0x1F2);
		inb(0x1F2);
		inb(0x3F6);
		inb(0x3F6);
		inb(0x1F2);
		inb(0x1F2);
	}
	while ((inb(0x1F2) & 0x80) && --tries);

	local_irq_restore(flags);

	outb(inb(0x1F4) & 0x07, 0x1F4);

	rt = inb(0x1F3);
	rt &= 0x07 << (3 * adev->devno);
	if (pio)
		rt |= (1 + 3 * pio) << (3 * adev->devno);

	udelay(100);
	outb(inb(0x1F2) | 0x01, 0x1F2);
	udelay(100);
	inb(0x1F5);

}