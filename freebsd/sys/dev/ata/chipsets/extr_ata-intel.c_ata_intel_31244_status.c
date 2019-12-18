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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ata_pci_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_sata_phy_check_events (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ata_intel_31244_status(device_t dev)
{
    /* do we have any PHY events ? */
    ata_sata_phy_check_events(dev, -1);

    /* any drive action to take care of ? */
    return ata_pci_status(dev);
}