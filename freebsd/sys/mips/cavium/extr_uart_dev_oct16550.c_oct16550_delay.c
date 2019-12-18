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
typedef  int u_char ;
struct uart_bas {int rclk; } ;

/* Variables and functions */
 int LCR_DLAB ; 
 int /*<<< orphan*/  REG_DLH ; 
 int /*<<< orphan*/  REG_DLL ; 
 int /*<<< orphan*/  REG_LCR ; 
 scalar_t__ delay_changed ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
oct16550_delay (struct uart_bas *bas)
{
	int divisor;
	u_char lcr;
        static int delay = 0;

        if (!delay_changed) return delay;
        delay_changed = 0;
	lcr = uart_getreg(bas, REG_LCR);
	uart_setreg(bas, REG_LCR, lcr | LCR_DLAB);
	uart_barrier(bas);
	divisor = uart_getreg(bas, REG_DLL) | (uart_getreg(bas, REG_DLH) << 8);
	uart_barrier(bas);
	uart_setreg(bas, REG_LCR, lcr);
	uart_barrier(bas);
	
	if(!bas->rclk)
		return 10; /* return an approx delay value */

	/* 1/10th the time to transmit 1 character (estimate). */
	if (divisor <= 134)
		return (16000000 * divisor / bas->rclk);
	return (16000 * divisor / (bas->rclk / 1000));

}