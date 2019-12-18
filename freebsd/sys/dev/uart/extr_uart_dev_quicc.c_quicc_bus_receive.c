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
typedef  int uint16_t ;
struct uart_bas {scalar_t__ chan; } ;
struct uart_softc {int /*<<< orphan*/  sc_hwmtx; struct uart_bas sc_bas; } ;

/* Variables and functions */
 int QUICC_PRAM_SCC_RBASE (scalar_t__) ; 
 int quicc_read2 (struct uart_bas*,int) ; 
 scalar_t__ quicc_read4 (struct uart_bas*,int) ; 
 int /*<<< orphan*/  quicc_write2 (struct uart_bas*,int,int) ; 
 int /*<<< orphan*/  uart_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_rx_put (struct uart_softc*,char volatile) ; 
 int /*<<< orphan*/  uart_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
quicc_bus_receive(struct uart_softc *sc)
{
	struct uart_bas *bas;
	volatile char *buf;
	uint16_t st, rb;

	bas = &sc->sc_bas;
	uart_lock(sc->sc_hwmtx);
	rb = quicc_read2(bas, QUICC_PRAM_SCC_RBASE(bas->chan - 1));
	st = quicc_read2(bas, rb);
	buf = (void *)(uintptr_t)quicc_read4(bas, rb + 4);
	uart_rx_put(sc, *buf);
	quicc_write2(bas, rb, st | 0x9000);
	uart_unlock(sc->sc_hwmtx);
	return (0);
}