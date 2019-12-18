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
struct uart_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  uart_opentty (struct uart_softc*) ; 
 int uart_stdio_backend (struct uart_softc*) ; 
 int uart_tty_backend (struct uart_softc*,char const*) ; 

int
uart_set_backend(struct uart_softc *sc, const char *opts)
{
	int retval;

	if (opts == NULL)
		return (0);

	if (strcmp("stdio", opts) == 0)
		retval = uart_stdio_backend(sc);
	else
		retval = uart_tty_backend(sc, opts);
	if (retval == 0)
		uart_opentty(sc);

	return (retval);
}