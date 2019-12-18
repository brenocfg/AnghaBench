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
 int /*<<< orphan*/  SAB_CMDR ; 
 int /*<<< orphan*/  SAB_CMDR_RFRD ; 
 int /*<<< orphan*/  SAB_CMDR_RMC ; 
 int /*<<< orphan*/  SAB_ISR0 ; 
 int SAB_ISR0_TCD ; 
 int /*<<< orphan*/  SAB_RFIFO ; 
 int /*<<< orphan*/  SAB_STAR ; 
 int SAB_STAR_CEC ; 
 int SAB_STAR_RFNE ; 
 int sab82532_delay (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_lock (struct mtx*) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_unlock (struct mtx*) ; 

__attribute__((used)) static int
sab82532_getc(struct uart_bas *bas, struct mtx *hwmtx)
{
	int c, delay;

	uart_lock(hwmtx);

	/* 1/10th the time to transmit 1 character (estimate). */
	delay = sab82532_delay(bas);

	while (!(uart_getreg(bas, SAB_STAR) & SAB_STAR_RFNE)) {
		uart_unlock(hwmtx);
		DELAY(delay);
		uart_lock(hwmtx);
	}

	while (uart_getreg(bas, SAB_STAR) & SAB_STAR_CEC)
		;
	uart_setreg(bas, SAB_CMDR, SAB_CMDR_RFRD);
	uart_barrier(bas);

	while (!(uart_getreg(bas, SAB_ISR0) & SAB_ISR0_TCD))
		DELAY(delay);

	c = uart_getreg(bas, SAB_RFIFO);
	uart_barrier(bas);

	/* Blow away everything left in the FIFO... */
	while (uart_getreg(bas, SAB_STAR) & SAB_STAR_CEC)
		;
	uart_setreg(bas, SAB_CMDR, SAB_CMDR_RMC);
	uart_barrier(bas);

	uart_unlock(hwmtx);

	return (c);
}