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
 int /*<<< orphan*/  UART_S1 ; 
 int UART_S1_RDRF ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vf_uart_rxready(struct uart_bas *bas)
{
	int usr1;

	usr1 = uart_getreg(bas, UART_S1);
	if (usr1 & UART_S1_RDRF) {
		return (1);
	}

	return (0);
}