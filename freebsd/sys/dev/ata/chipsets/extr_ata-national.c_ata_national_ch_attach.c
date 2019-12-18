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
struct TYPE_2__ {int alignment; int max_iosize; } ;
struct ata_channel {TYPE_1__ dma; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int DEV_BSIZE ; 
 int ata_pci_ch_attach (int /*<<< orphan*/ ) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ata_national_ch_attach(device_t dev)
{
	struct ata_channel *ch = device_get_softc(dev);
 
	ch->dma.alignment = 16;
	ch->dma.max_iosize = 64 * DEV_BSIZE;
	return (ata_pci_ch_attach(dev));
}