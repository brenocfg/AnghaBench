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

/* Variables and functions */
 int /*<<< orphan*/  UART01x_DR ; 
 int /*<<< orphan*/  UART01x_FR ; 
 int UART01x_FR_TXFF ; 
 int UART_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_WRITE (char,int /*<<< orphan*/ ) ; 

void prom_putchar(char c)
{
	UART_WRITE(c, UART01x_DR);
	while ((UART_READ(UART01x_FR) & UART01x_FR_TXFF) != 0)
		;
}