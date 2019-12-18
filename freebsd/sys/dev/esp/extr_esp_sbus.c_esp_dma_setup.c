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
 int DMA_SETUP (int /*<<< orphan*/ ,void**,size_t*,int,size_t*) ; 

__attribute__((used)) static int
esp_dma_setup(struct ncr53c9x_softc *sc, void **addr, size_t *len,
    int datain, size_t *dmasize)
{
	struct esp_softc *esc = (struct esp_softc *)sc;

	return (DMA_SETUP(esc->sc_dma, addr, len, datain, dmasize));
}