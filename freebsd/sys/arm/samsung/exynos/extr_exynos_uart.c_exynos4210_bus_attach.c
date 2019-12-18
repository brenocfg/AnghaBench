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
struct uart_softc {scalar_t__ sc_hwoflow; scalar_t__ sc_hwiflow; } ;

/* Variables and functions */

__attribute__((used)) static int
exynos4210_bus_attach(struct uart_softc *sc)
{

	sc->sc_hwiflow = 0;
	sc->sc_hwoflow = 0;

	return (0);
}