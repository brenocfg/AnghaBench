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
struct esp_softc {int /*<<< orphan*/  sc_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_GO (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
esp_dma_go(struct ncr53c9x_softc *sc)
{
	struct esp_softc *esc = (struct esp_softc *)sc;

	DMA_GO(esc->sc_dma);
}