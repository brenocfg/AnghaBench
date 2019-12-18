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
 int /*<<< orphan*/  UART_DR ; 
 int __uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_pl011_rxready (struct uart_bas*) ; 

__attribute__((used)) static int
uart_pl011_getc(struct uart_bas *bas, struct mtx *hwmtx)
{
	int c;

	while (!uart_pl011_rxready(bas))
		;
	c = __uart_getreg(bas, UART_DR) & 0xff;

	return (c);
}