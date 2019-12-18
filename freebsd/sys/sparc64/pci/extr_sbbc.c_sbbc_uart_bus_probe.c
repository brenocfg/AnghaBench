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
struct uart_softc {void* sc_txfifosz; void* sc_rxfifosz; struct uart_bas sc_bas; } ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ SBBC_CONS_OFF (int /*<<< orphan*/ ) ; 
 void* SBBC_SRAM_READ_4 (scalar_t__) ; 
 int /*<<< orphan*/  cons_in_begin ; 
 int /*<<< orphan*/  cons_in_end ; 
 int /*<<< orphan*/  cons_out_begin ; 
 int /*<<< orphan*/  cons_out_end ; 
 scalar_t__ sbbc_console ; 
 scalar_t__ sbbc_solcons ; 

__attribute__((used)) static int
sbbc_uart_bus_probe(struct uart_softc *sc)
{
	struct uart_bas *bas;
	bus_space_tag_t bst;
	bus_space_handle_t bsh;

	if (sbbc_console != 0) {
		bas = &sc->sc_bas;
		bst = bas->bst;
		bsh = bas->bsh;
		sc->sc_rxfifosz = SBBC_SRAM_READ_4(sbbc_solcons +
		    SBBC_CONS_OFF(cons_in_end)) - SBBC_SRAM_READ_4(sbbc_solcons +
		    SBBC_CONS_OFF(cons_in_begin)) - 1;
		sc->sc_txfifosz = SBBC_SRAM_READ_4(sbbc_solcons +
		    SBBC_CONS_OFF(cons_out_end)) - SBBC_SRAM_READ_4(sbbc_solcons +
		    SBBC_CONS_OFF(cons_out_begin)) - 1;
		return (0);
	}
	return (ENXIO);
}