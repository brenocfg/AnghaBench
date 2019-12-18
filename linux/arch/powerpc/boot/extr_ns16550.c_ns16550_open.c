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
 int UART_FCR ; 
 int /*<<< orphan*/  out_8 (scalar_t__,int) ; 
 scalar_t__ reg_base ; 
 int reg_shift ; 

__attribute__((used)) static int ns16550_open(void)
{
	out_8(reg_base + (UART_FCR << reg_shift), 0x06);
	return 0;
}