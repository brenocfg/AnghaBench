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
struct consdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AML_UART_RFIFO_REG ; 
 int /*<<< orphan*/  AML_UART_STATUS_REG ; 
 int AML_UART_STATUS_RX_FIFO_EMPTY ; 
 int ub_getreg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uart_cngetc(struct consdev * cp)
{
	int c;

	if ((ub_getreg(AML_UART_STATUS_REG) &
	    AML_UART_STATUS_RX_FIFO_EMPTY) != 0)
		return (-1);

	c = ub_getreg(AML_UART_RFIFO_REG) & 0xff;

	return (c);
}