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
struct ata_channel {int flags; scalar_t__ unit; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATA_NO_SLAVE ; 
 int ATA_USE_16BIT ; 
 int /*<<< orphan*/  ata_generic_hw (int /*<<< orphan*/ ) ; 
 int ata_probe (int /*<<< orphan*/ ) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_iobus_sub_probe(device_t dev)
{
	struct ata_channel *ch = device_get_softc(dev);

	/* Only a single unit per controller thus far */
	ch->unit = 0;
	ch->flags = (ATA_USE_16BIT|ATA_NO_SLAVE);
	ata_generic_hw(dev);

	return ata_probe(dev);
}