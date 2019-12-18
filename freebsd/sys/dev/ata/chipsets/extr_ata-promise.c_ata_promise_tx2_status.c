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
struct ata_channel {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_BMDEVSPEC_0 ; 
 int /*<<< orphan*/  ATA_BMDEVSPEC_1 ; 
 int ATA_IDX_INB (struct ata_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_IDX_OUTB (struct ata_channel*,int /*<<< orphan*/ ,int) ; 
 int ata_pci_status (int /*<<< orphan*/ ) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_promise_tx2_status(device_t dev)
{
    struct ata_channel *ch = device_get_softc(dev);

    ATA_IDX_OUTB(ch, ATA_BMDEVSPEC_0, 0x0b);
    if (ATA_IDX_INB(ch, ATA_BMDEVSPEC_1) & 0x20) {
	return ata_pci_status(dev);
    }
    return 0;
}