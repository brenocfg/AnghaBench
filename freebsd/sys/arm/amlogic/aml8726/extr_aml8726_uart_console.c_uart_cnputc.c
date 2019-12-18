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
 int /*<<< orphan*/  AML_UART_STATUS_REG ; 
 int AML_UART_STATUS_TX_FIFO_FULL ; 
 int /*<<< orphan*/  AML_UART_WFIFO_REG ; 
 int /*<<< orphan*/  cpu_spinwait () ; 
 int ub_getreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ub_setreg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
uart_cnputc(struct consdev *cp, int c)
{

	while ((ub_getreg(AML_UART_STATUS_REG) &
	    AML_UART_STATUS_TX_FIFO_FULL) != 0)
		cpu_spinwait();

	ub_setreg(AML_UART_WFIFO_REG, c);
}