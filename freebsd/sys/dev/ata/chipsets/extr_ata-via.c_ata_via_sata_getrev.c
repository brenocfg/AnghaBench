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
struct ata_channel {scalar_t__ unit; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
ata_via_sata_getrev(device_t dev, int target)
{
	device_t parent = device_get_parent(dev);
	struct ata_channel *ch = device_get_softc(dev);

	if (ch->unit == 0) {
		if (pci_read_config(parent, 0xa0 + target, 1) & 0x10)
			return (2);
		else
			return (1);
	}
	return (0);
}