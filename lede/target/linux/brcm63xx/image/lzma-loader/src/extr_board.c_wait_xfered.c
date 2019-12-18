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
 unsigned int READREG (scalar_t__) ; 
 scalar_t__ UART_IR_REG ; 
 scalar_t__ uart_base ; 

__attribute__((used)) static void wait_xfered(void)
{
        unsigned int val;

        do {
                val = READREG(uart_base + UART_IR_REG);
                if (val & (1 << 5))
                        break;
        } while (1);
}