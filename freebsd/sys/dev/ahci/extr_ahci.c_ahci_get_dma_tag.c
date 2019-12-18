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
struct ahci_controller {int /*<<< orphan*/  dma_tag; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;

/* Variables and functions */
 struct ahci_controller* device_get_softc (int /*<<< orphan*/ ) ; 

bus_dma_tag_t
ahci_get_dma_tag(device_t dev, device_t child)
{
	struct ahci_controller *ctlr = device_get_softc(dev);

	return (ctlr->dma_tag);
}