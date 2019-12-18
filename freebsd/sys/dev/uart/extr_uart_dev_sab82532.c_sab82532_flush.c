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
struct uart_bas {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAB_CMDR ; 
 int /*<<< orphan*/  SAB_CMDR_RRES ; 
 int /*<<< orphan*/  SAB_CMDR_XRES ; 
 int /*<<< orphan*/  SAB_STAR ; 
 int SAB_STAR_CEC ; 
 int UART_FLUSH_RECEIVER ; 
 int UART_FLUSH_TRANSMITTER ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sab82532_flush(struct uart_bas *bas, int what)
{

	if (what & UART_FLUSH_TRANSMITTER) {
		while (uart_getreg(bas, SAB_STAR) & SAB_STAR_CEC)
			;
		uart_setreg(bas, SAB_CMDR, SAB_CMDR_XRES);
		uart_barrier(bas);
	}
	if (what & UART_FLUSH_RECEIVER) {
		while (uart_getreg(bas, SAB_STAR) & SAB_STAR_CEC)
			;
		uart_setreg(bas, SAB_CMDR, SAB_CMDR_RRES);
		uart_barrier(bas);
	}
}