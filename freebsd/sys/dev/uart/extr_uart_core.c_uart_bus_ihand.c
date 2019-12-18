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
typedef  int /*<<< orphan*/  serdev_intr_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  SER_INT_BREAK 132 
#define  SER_INT_OVERRUN 131 
#define  SER_INT_RXREADY 130 
#define  SER_INT_SIGCHG 129 
#define  SER_INT_TXIDLE 128 
 int /*<<< orphan*/ * uart_intr_break ; 
 int /*<<< orphan*/ * uart_intr_overrun ; 
 int /*<<< orphan*/ * uart_intr_rxready ; 
 int /*<<< orphan*/ * uart_intr_sigchg ; 
 int /*<<< orphan*/ * uart_intr_txidle ; 

serdev_intr_t *
uart_bus_ihand(device_t dev, int ipend)
{

	switch (ipend) {
	case SER_INT_BREAK:
		return (uart_intr_break);
	case SER_INT_OVERRUN:
		return (uart_intr_overrun);
	case SER_INT_RXREADY:
		return (uart_intr_rxready);
	case SER_INT_SIGCHG:
		return (uart_intr_sigchg);
	case SER_INT_TXIDLE:
		return (uart_intr_txidle);
	}
	return (NULL);
}