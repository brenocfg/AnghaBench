#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long pio_base; } ;

/* Variables and functions */
 TYPE_1__ udbg_uart ; 
 int /*<<< orphan*/  udbg_uart_in ; 
 int /*<<< orphan*/  udbg_uart_in_pio ; 
 int /*<<< orphan*/  udbg_uart_out ; 
 int /*<<< orphan*/  udbg_uart_out_pio ; 
 unsigned int udbg_uart_stride ; 
 int /*<<< orphan*/  udbg_use_uart () ; 

void udbg_uart_init_pio(unsigned long port, unsigned int stride)
{
	if (!port)
		return;
	udbg_uart.pio_base = port;
	udbg_uart_stride = stride;
	udbg_uart_in = udbg_uart_in_pio;
	udbg_uart_out = udbg_uart_out_pio;
	udbg_use_uart();
}