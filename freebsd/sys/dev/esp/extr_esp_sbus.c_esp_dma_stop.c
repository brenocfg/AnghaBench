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
 int D_EN_DMA ; 
 int L64854_GCSR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L64854_SCSR (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
esp_dma_stop(struct ncr53c9x_softc *sc)
{
	struct esp_softc *esc = (struct esp_softc *)sc;

	L64854_SCSR(esc->sc_dma, L64854_GCSR(esc->sc_dma) & ~D_EN_DMA);
}