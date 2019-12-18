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
struct uart_bas {int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
struct uart_softc {struct uart_bas sc_bas; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSCOM_UFSTAT ; 
 int /*<<< orphan*/  SSCOM_URXH ; 
 int UFSTAT_RXCOUNT ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_rx_put (struct uart_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
exynos4210_bus_receive(struct uart_softc *sc)
{
	struct uart_bas *bas;

	bas = &sc->sc_bas;
	while (bus_space_read_4(bas->bst, bas->bsh,
		SSCOM_UFSTAT) & UFSTAT_RXCOUNT)
		uart_rx_put(sc, uart_getreg(&sc->sc_bas, SSCOM_URXH));

	return (0);
}