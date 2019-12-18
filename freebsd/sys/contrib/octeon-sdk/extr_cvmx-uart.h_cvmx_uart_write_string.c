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
 int /*<<< orphan*/  cvmx_uart_write_byte (int,char const) ; 

__attribute__((used)) static inline void cvmx_uart_write_string(int uart_index, const char *str)
{
    /* Just loop writing one byte at a time */
    while (*str)
    {
        cvmx_uart_write_byte(uart_index, *str);
        str++;
    }
}