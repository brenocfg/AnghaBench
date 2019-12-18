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
struct ata_channel {int /*<<< orphan*/  flags; TYPE_1__ hw; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CHECKS_CABLE ; 
 int ENXIO ; 
 scalar_t__ ata_pci_ch_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_promise_tx2_status ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_promise_tx2_ch_attach(device_t dev)
{
    struct ata_channel *ch = device_get_softc(dev);

    if (ata_pci_ch_attach(dev))
	return ENXIO;

    ch->hw.status = ata_promise_tx2_status;
    ch->flags |= ATA_CHECKS_CABLE;
    return 0;
}