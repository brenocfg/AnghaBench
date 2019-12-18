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
struct uart_softc {int dll; int dlh; int /*<<< orphan*/  mcr; int /*<<< orphan*/  msr; } ;

/* Variables and functions */
 int DEFAULT_BAUD ; 
 int DEFAULT_RCLK ; 
 int /*<<< orphan*/  modem_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxfifo_reset (struct uart_softc*,int) ; 

__attribute__((used)) static void
uart_reset(struct uart_softc *sc)
{
	uint16_t divisor;

	divisor = DEFAULT_RCLK / DEFAULT_BAUD / 16;
	sc->dll = divisor;
	sc->dlh = divisor >> 16;
	sc->msr = modem_status(sc->mcr);

	rxfifo_reset(sc, 1);	/* no fifo until enabled by software */
}