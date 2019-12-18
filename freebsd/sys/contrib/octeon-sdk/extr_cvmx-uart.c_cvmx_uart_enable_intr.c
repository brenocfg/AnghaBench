#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cvmx_uart_intr_handler_t ;
struct TYPE_3__ {int erbfi; } ;
struct TYPE_4__ {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_uart_ier_t ;

/* Variables and functions */
 scalar_t__ CVMX_IRQ_UART0 ; 
 int /*<<< orphan*/  CVMX_MIO_UARTX_IER (int) ; 
 int /*<<< orphan*/  cvmx_interrupt_register (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_interrupt_unmask_irq (scalar_t__) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cvmx_uart_enable_intr(int uart, cvmx_uart_intr_handler_t handler)
{
#ifndef CVMX_BUILD_FOR_LINUX_KERNEL
    cvmx_uart_ier_t ier;

    cvmx_interrupt_register(CVMX_IRQ_UART0 + uart, handler, NULL);
    /* Enable uart interrupts for debugger Control-C processing */
    ier.u64 = cvmx_read_csr(CVMX_MIO_UARTX_IER(uart));
    ier.s.erbfi = 1;
    cvmx_write_csr(CVMX_MIO_UARTX_IER(uart), ier.u64);

    cvmx_interrupt_unmask_irq(CVMX_IRQ_UART0 + uart);
#endif
}