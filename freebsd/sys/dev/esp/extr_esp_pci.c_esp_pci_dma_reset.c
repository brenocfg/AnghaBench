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
struct ncr53c9x_softc {int dummy; } ;
struct esp_pci_softc {scalar_t__ sc_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMACMD_IDLE ; 
 int /*<<< orphan*/  DMA_CMD ; 
 int /*<<< orphan*/  WRITE_DMAREG (struct esp_pci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
esp_pci_dma_reset(struct ncr53c9x_softc *sc)
{
	struct esp_pci_softc *esc = (struct esp_pci_softc *)sc;

	WRITE_DMAREG(esc, DMA_CMD, DMACMD_IDLE);

	esc->sc_active = 0;
}