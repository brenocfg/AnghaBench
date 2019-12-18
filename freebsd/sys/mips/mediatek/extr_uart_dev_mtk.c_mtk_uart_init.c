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
struct uart_bas {int rclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_CDDL_REG ; 
 int UART_LCR_5B ; 
 int UART_LCR_6B ; 
 int UART_LCR_7B ; 
 int UART_LCR_8B ; 
 int UART_LCR_EVEN ; 
 int UART_LCR_PEN ; 
 int /*<<< orphan*/  UART_LCR_REG ; 
 int UART_LCR_STB_15 ; 
#define  UART_PARITY_EVEN 130 
#define  UART_PARITY_NONE 129 
#define  UART_PARITY_ODD 128 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mtk_uart_init(struct uart_bas *bas, int baudrate, int databits,
    int stopbits, int parity)
{
        /* CLKDIV  = 384000000/ 3/ 16/ br */
        /* for 384MHz CLKDIV = 8000000 / baudrate; */
        switch (databits) {
        case 5:
    		databits = UART_LCR_5B;
    		break;
        case 6:
    		databits = UART_LCR_6B;
    		break;
        case 7:
    		databits = UART_LCR_7B;
    		break;
        case 8:
    		databits = UART_LCR_8B;
    		break;
    	default:
    		/* Unsupported */
    		return;
        }
	switch (parity) {
	case UART_PARITY_EVEN:	parity = (UART_LCR_PEN|UART_LCR_EVEN); break;
	case UART_PARITY_ODD:	parity = (UART_LCR_PEN); break;
	case UART_PARITY_NONE:	parity = 0; break;
	/* Unsupported */
	default:		return;
	}

	if (bas->rclk && baudrate) {
        	uart_setreg(bas, UART_CDDL_REG, bas->rclk/16/baudrate);
		uart_barrier(bas);
	}

        uart_setreg(bas, UART_LCR_REG, databits |
				(stopbits==1?0:UART_LCR_STB_15) |
       			 	parity);
	uart_barrier(bas);
}