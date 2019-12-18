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
struct lsi64854_softc {int dummy; } ;
struct le_dma_softc {struct lsi64854_softc* sc_dma; } ;
struct lance_softc {int dummy; } ;

/* Variables and functions */
 int DMA_INTR (struct lsi64854_softc*) ; 

__attribute__((used)) static int
le_dma_hwintr(struct lance_softc *sc)
{
	struct le_dma_softc *lesc = (struct le_dma_softc *)sc;
	struct lsi64854_softc *dma = lesc->sc_dma;

	return (DMA_INTR(dma));
}