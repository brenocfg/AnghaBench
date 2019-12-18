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
typedef  int /*<<< orphan*/  bus_dma_tag_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bus_dma_tag_t
ata_pci_get_dma_tag(device_t bus, device_t child)
{

	return (bus_get_dma_tag(bus));
}