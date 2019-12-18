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
struct ti_sdma_softc {scalar_t__ sc_hw_rev; } ;

/* Variables and functions */
 scalar_t__ DMA4_OMAP4_REV ; 

__attribute__((used)) static inline int
ti_sdma_is_omap4_rev(struct ti_sdma_softc *sc)
{
	return (sc->sc_hw_rev == DMA4_OMAP4_REV);
}