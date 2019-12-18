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
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  UART_DM_CR ; 
 int /*<<< orphan*/  UART_DM_RESET_ERROR_STATUS ; 
 int /*<<< orphan*/  UART_DM_RF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_DM_SR ; 
 int UART_DM_SR_RXRDY ; 
 int UART_DM_SR_UART_OVERRUN ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (struct mtx*) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (struct mtx*) ; 

__attribute__((used)) static int
msm_getc(struct uart_bas *bas, struct mtx *mtx)
{
	int c;

	uart_lock(mtx);

	/* Wait for a character to come ready */
	while ((uart_getreg(bas, UART_DM_SR) & UART_DM_SR_RXRDY) !=
	    UART_DM_SR_RXRDY)
		DELAY(4);

	/* Check for Overrun error. If so reset Error Status */
	if (uart_getreg(bas, UART_DM_SR) & UART_DM_SR_UART_OVERRUN)
		uart_setreg(bas, UART_DM_CR, UART_DM_RESET_ERROR_STATUS);

	/* Read char */
	c = uart_getreg(bas, UART_DM_RF(0));

	uart_unlock(mtx);

	return (c);
}