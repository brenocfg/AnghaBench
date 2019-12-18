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
 int /*<<< orphan*/  AR933X_UART_DATA_REG ; 
 int AR933X_UART_DATA_RX_CSR ; 
 int ar933x_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ar933x_rxready(struct uart_bas *bas)
{

	/* Wait for a character to come ready */
	return (!!(ar933x_getreg(bas, AR933X_UART_DATA_REG)
	    & AR933X_UART_DATA_RX_CSR));
}