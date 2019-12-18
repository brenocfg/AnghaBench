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
 int /*<<< orphan*/  cvmx_debug_uart ; 
 int /*<<< orphan*/  cvmx_debug_uart_process_debug_interrupt ; 
 int /*<<< orphan*/  cvmx_uart_enable_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cvmx_debug_uart_install_break_handler(void)
{
#ifndef CVMX_BUILD_FOR_LINUX_KERNEL
#ifdef CVMX_BUILD_FOR_TOOLCHAIN
    if (cvmx_uart_enable_intr)
#endif
        cvmx_uart_enable_intr(cvmx_debug_uart, cvmx_debug_uart_process_debug_interrupt);
#endif
}