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
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  SAB_STAR ; 
 int SAB_STAR_TEC ; 
 int /*<<< orphan*/  SAB_TIC ; 
 int sab82532_delay (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
sab82532_putc(struct uart_bas *bas, int c)
{
	int delay, limit;

	/* 1/10th the time to transmit 1 character (estimate). */
	delay = sab82532_delay(bas);

	limit = 20;
	while ((uart_getreg(bas, SAB_STAR) & SAB_STAR_TEC) && --limit)
		DELAY(delay);
	uart_setreg(bas, SAB_TIC, c);
	limit = 20;
	while ((uart_getreg(bas, SAB_STAR) & SAB_STAR_TEC) && --limit)
		DELAY(delay);
}