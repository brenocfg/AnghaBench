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
struct tty {int dummy; } ;
struct altera_jtag_uart_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AJU_LOCK (struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  AJU_UNLOCK (struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  aju_handle_output (struct altera_jtag_uart_softc*,struct tty*) ; 
 int /*<<< orphan*/  tty_lock_assert (struct tty*,int /*<<< orphan*/ ) ; 
 struct altera_jtag_uart_softc* tty_softc (struct tty*) ; 

__attribute__((used)) static void
aju_outwakeup(struct tty *tp)
{
	struct altera_jtag_uart_softc *sc = tty_softc(tp);

	tty_lock_assert(tp, MA_OWNED);

	AJU_LOCK(sc);
	aju_handle_output(sc, tp);
	AJU_UNLOCK(sc);
}