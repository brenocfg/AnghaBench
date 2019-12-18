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
 int /*<<< orphan*/  CVMX_CLOCK_SCLK ; 
 int /*<<< orphan*/  cvmx_clock_get_rate (int /*<<< orphan*/ ) ; 
 int cvmx_uart_setup2 (int,int /*<<< orphan*/ ,int) ; 

int cvmx_uart_setup (int uart_index)
{
    return cvmx_uart_setup2(uart_index, cvmx_clock_get_rate (CVMX_CLOCK_SCLK), 115200);
}