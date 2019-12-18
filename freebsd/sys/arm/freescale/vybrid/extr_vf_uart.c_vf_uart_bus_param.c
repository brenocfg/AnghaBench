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
struct uart_softc {int /*<<< orphan*/  sc_hwmtx; int /*<<< orphan*/  sc_bas; } ;

/* Variables and functions */
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vf_uart_init (int /*<<< orphan*/ *,int,int,int,int) ; 

__attribute__((used)) static int
vf_uart_bus_param(struct uart_softc *sc, int baudrate, int databits,
    int stopbits, int parity)
{

	uart_lock(sc->sc_hwmtx);
	vf_uart_init(&sc->sc_bas, baudrate, databits, stopbits, parity);
	uart_unlock(sc->sc_hwmtx);

	return (0);
}