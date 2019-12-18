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
typedef  int uint32_t ;
struct tty {int dummy; } ;
struct altera_jtag_uart_softc {struct tty* ajus_ttyp; } ;

/* Variables and functions */
 int /*<<< orphan*/  AJU_LOCK (struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  AJU_UNLOCK (struct altera_jtag_uart_softc*) ; 
 int ALTERA_JTAG_UART_CONTROL_RI ; 
 int ALTERA_JTAG_UART_CONTROL_WI ; 
 int aju_control_read (struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  aju_handle_input (struct altera_jtag_uart_softc*,struct tty*) ; 
 int /*<<< orphan*/  aju_handle_output (struct altera_jtag_uart_softc*,struct tty*) ; 
 int /*<<< orphan*/  aju_intr_read_count ; 
 int /*<<< orphan*/  aju_intr_write_count ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 

__attribute__((used)) static void
aju_intr(void *arg)
{
	struct altera_jtag_uart_softc *sc = arg;
	struct tty *tp = sc->ajus_ttyp;
	uint32_t v;

	tty_lock(tp);
	AJU_LOCK(sc);
	v = aju_control_read(sc);
	if (v & ALTERA_JTAG_UART_CONTROL_RI) {
		atomic_add_int(&aju_intr_read_count, 1);
		aju_handle_input(sc, tp);
	}
	if (v & ALTERA_JTAG_UART_CONTROL_WI) {
		atomic_add_int(&aju_intr_write_count, 1);
		aju_handle_output(sc, tp);
	}
	AJU_UNLOCK(sc);
	tty_unlock(tp);
}