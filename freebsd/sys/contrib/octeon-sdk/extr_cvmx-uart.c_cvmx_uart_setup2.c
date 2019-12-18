#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint16_t ;
struct TYPE_8__ {int afce; int rts; } ;
struct TYPE_10__ {int u64; TYPE_2__ s; } ;
typedef  TYPE_4__ cvmx_uart_mcr_t ;
struct TYPE_9__ {int eps; int dlab; scalar_t__ pen; scalar_t__ stop; int /*<<< orphan*/  cls; } ;
struct TYPE_11__ {int u64; TYPE_3__ s; } ;
typedef  TYPE_5__ cvmx_uart_lcr_t ;
struct TYPE_7__ {int en; int rxfr; int txfr; } ;
struct TYPE_12__ {int u64; TYPE_1__ s; } ;
typedef  TYPE_6__ cvmx_uart_fcr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_MF_CYCLE (scalar_t__) ; 
 int /*<<< orphan*/  CVMX_MIO_UARTX_DLH (int) ; 
 int /*<<< orphan*/  CVMX_MIO_UARTX_DLL (int) ; 
 int /*<<< orphan*/  CVMX_MIO_UARTX_FCR (int) ; 
 int /*<<< orphan*/  CVMX_MIO_UARTX_LCR (int) ; 
 int /*<<< orphan*/  CVMX_MIO_UARTX_LSR (int) ; 
 int /*<<< orphan*/  CVMX_MIO_UARTX_MCR (int) ; 
 int /*<<< orphan*/  CVMX_UART_BITS8 ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_uart_simulator_p () ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 

int cvmx_uart_setup2(int uart_index, int cpu_clock_hertz, int baudrate)
{
    uint16_t divisor;
    cvmx_uart_fcr_t fcrval;
    cvmx_uart_mcr_t mcrval;
    cvmx_uart_lcr_t lcrval;

    fcrval.u64 = 0;
    fcrval.s.en = 1;    /* enable the FIFO's */
    fcrval.s.rxfr = 1;  /* reset the RX fifo */
    fcrval.s.txfr = 1;  /* reset the TX fifo */

    if (cvmx_uart_simulator_p())
        divisor = 1;
    else
        divisor = ((unsigned long)(cpu_clock_hertz + 8 * baudrate) / (unsigned long)(16 * baudrate));

    cvmx_write_csr(CVMX_MIO_UARTX_FCR(uart_index), fcrval.u64);

    mcrval.u64 = 0;
    if (uart_index == 1 && cvmx_uart_simulator_p())
      mcrval.s.afce = 1;  /* enable auto flow control for simulator. Needed for  gdb regression callfuncs.exp. */
    else
      mcrval.s.afce = 0;  /* disable auto flow control so board can power on without serial port connected */

    mcrval.s.rts = 1;   /* looks like this must be set for auto flow control to work */

    cvmx_read_csr(CVMX_MIO_UARTX_LSR(uart_index));

    lcrval.u64 = 0;
    lcrval.s.cls = CVMX_UART_BITS8;
    lcrval.s.stop = 0;  /* stop bit included? */
    lcrval.s.pen = 0;   /* no parity? */
    lcrval.s.eps = 1;   /* even parity? */
    lcrval.s.dlab = 1;  /* temporary to program the divisor */
    cvmx_write_csr(CVMX_MIO_UARTX_LCR(uart_index), lcrval.u64);

    cvmx_write_csr(CVMX_MIO_UARTX_DLL(uart_index), divisor & 0xff);
    cvmx_write_csr(CVMX_MIO_UARTX_DLH(uart_index), (divisor>>8) & 0xff);

    lcrval.s.dlab = 0;  /* divisor is programmed now, set this back to normal */
    cvmx_write_csr(CVMX_MIO_UARTX_LCR(uart_index), lcrval.u64);

    /* spec says need to wait after you program the divisor */
    if (!cvmx_uart_simulator_p())
    {
        uint64_t read_cycle;
        CVMX_MF_CYCLE (read_cycle);
        read_cycle += (2 * divisor * 16) + 10000;

        /* Spin */
        while (1)
        {
            uint64_t new_cycle;
            CVMX_MF_CYCLE (new_cycle);
            if (new_cycle >= read_cycle)
                break;
        }
    }

    /* Don't enable flow control until after baud rate is configured. - we don't want
    ** to allow characters in until after the baud rate is fully configured */
    cvmx_write_csr(CVMX_MIO_UARTX_MCR(uart_index), mcrval.u64);
    return 0;

}