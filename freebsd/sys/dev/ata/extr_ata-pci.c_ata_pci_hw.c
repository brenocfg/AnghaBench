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
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
struct ata_channel {TYPE_1__ hw; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ata_generic_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_pci_status ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 

void
ata_pci_hw(device_t dev)
{
    struct ata_channel *ch = device_get_softc(dev);

    ata_generic_hw(dev);
    ch->hw.status = ata_pci_status;
}