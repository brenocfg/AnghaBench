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
struct sunkbd_softc {scalar_t__ sc_polling; int /*<<< orphan*/ * sc_sysdev; int /*<<< orphan*/ * sc_uart; scalar_t__ sc_repeating; scalar_t__* sc_buffered_char; } ;
typedef  int /*<<< orphan*/  keyboard_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  KBD_IS_ACTIVE (int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int /*<<< orphan*/  uart_rx_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ uart_rxready (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sunkbd_check(keyboard_t *kbd)
{
	struct sunkbd_softc *sc;

	if (!KBD_IS_ACTIVE(kbd))
		return (FALSE);

	sc = (struct sunkbd_softc *)kbd;

#if defined(SUNKBD_EMULATE_ATKBD)
	if (sc->sc_buffered_char[0])
		return (TRUE);
#endif

	if (sc->sc_repeating)
		return (TRUE);

	if (sc->sc_uart != NULL && !uart_rx_empty(sc->sc_uart))
		return (TRUE);

	if (sc->sc_polling != 0 && sc->sc_sysdev != NULL &&
	    uart_rxready(sc->sc_sysdev))
		return (TRUE);

	return (FALSE);
}