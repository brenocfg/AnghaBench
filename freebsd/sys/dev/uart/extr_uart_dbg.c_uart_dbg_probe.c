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
 int /*<<< orphan*/  UART_DEV_DBGPORT ; 
 scalar_t__ uart_cpu_getdev (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_dbgport ; 
 scalar_t__ uart_probe (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
uart_dbg_probe(void)
{

	if (uart_cpu_getdev(UART_DEV_DBGPORT, &uart_dbgport))
		return (-1);

	if (uart_probe(&uart_dbgport))
		return (-1);

	return (0);
}