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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {scalar_t__ dr; } ;
struct TYPE_4__ {void* u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_uart_lsr_t ;

/* Variables and functions */
 int CVMX_IRQ_UART0 ; 
 int /*<<< orphan*/  CVMX_MIO_UARTX_LSR (int) ; 
 int /*<<< orphan*/  CVMX_MIO_UARTX_RBR (int) ; 
 int __octeon_uart_trylock () ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_break_interrupt(int irq_number, uint64_t registers[32], void *user_arg)
{
    /* Exclude new functionality when building with older toolchains */
#if OCTEON_APP_INIT_H_VERSION >= 3
    int uart = irq_number - CVMX_IRQ_UART0;
    cvmx_uart_lsr_t lsrval;

    /* Check for a Control-C interrupt from the console. This loop will eat
        all input received on the uart */
    lsrval.u64 = cvmx_read_csr(CVMX_MIO_UARTX_LSR(uart));
    while (lsrval.s.dr)
    {
        int c = cvmx_read_csr(CVMX_MIO_UARTX_RBR(uart));
        if (c == '\003')
        {
            register uint64_t tmp;

            /* Wait for an another Control-C if right now we have no
               access to the console.  After this point we hold the
               lock and use a different lock to synchronize between
               the memfile dumps from different cores.  As a
               consequence regular printfs *don't* work after this
               point! */
            if (__octeon_uart_trylock () == 1)
                return;

            /* Pulse MCD0 signal on Ctrl-C to stop all the cores. Also
               set the MCD0 to be not masked by this core so we know
               the signal is received by someone */
            asm volatile (
                "dmfc0 %0, $22\n"
                "ori   %0, %0, 0x1110\n"
                "dmtc0 %0, $22\n"
                : "=r" (tmp));
        }
        lsrval.u64 = cvmx_read_csr(CVMX_MIO_UARTX_LSR(uart));
    }
#endif
}