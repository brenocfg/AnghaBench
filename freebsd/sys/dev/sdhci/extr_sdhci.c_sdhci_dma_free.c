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
struct sdhci_slot {int /*<<< orphan*/  dmatag; int /*<<< orphan*/  dmamap; int /*<<< orphan*/  dmamem; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sdhci_dma_free(struct sdhci_slot *slot)
{

	bus_dmamap_unload(slot->dmatag, slot->dmamap);
	bus_dmamem_free(slot->dmatag, slot->dmamem, slot->dmamap);
	bus_dma_tag_destroy(slot->dmatag);
}