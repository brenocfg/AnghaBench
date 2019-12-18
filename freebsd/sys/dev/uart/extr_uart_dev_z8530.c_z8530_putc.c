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
 int BES_TXE ; 
 int /*<<< orphan*/  REG_CTRL ; 
 int /*<<< orphan*/  REG_DATA ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
z8530_putc(struct uart_bas *bas, int c)
{

	while (!(uart_getreg(bas, REG_CTRL) & BES_TXE))
		;
	uart_setreg(bas, REG_DATA, c);
	uart_barrier(bas);
}