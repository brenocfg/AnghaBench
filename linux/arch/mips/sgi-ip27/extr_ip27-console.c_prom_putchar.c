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
struct ioc3_uartregs {int /*<<< orphan*/  iu_thr; int /*<<< orphan*/  iu_lsr; } ;

/* Variables and functions */
 struct ioc3_uartregs* console_uart () ; 
 int readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (char,int /*<<< orphan*/ *) ; 

void prom_putchar(char c)
{
	struct ioc3_uartregs *uart = console_uart();

	while ((readb(&uart->iu_lsr) & 0x20) == 0)
		;
	writeb(c, &uart->iu_thr);
}