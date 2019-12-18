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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {scalar_t__ pio_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  inb (scalar_t__) ; 
 TYPE_1__ udbg_uart ; 
 unsigned int udbg_uart_stride ; 

__attribute__((used)) static u8 udbg_uart_in_pio(unsigned int reg)
{
	return inb(udbg_uart.pio_base + (reg * udbg_uart_stride));
}