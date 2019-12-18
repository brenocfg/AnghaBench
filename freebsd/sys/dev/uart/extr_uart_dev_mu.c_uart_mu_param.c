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
typedef  int uint32_t ;
struct uart_bas {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_MU_BAUD_REG ; 
 int /*<<< orphan*/  AUX_MU_CNTL_REG ; 
 int /*<<< orphan*/  AUX_MU_LCR_REG ; 
 int CNTL_RXENAB ; 
 int CNTL_TXENAB ; 
 int CPU_CLOCK ; 
 int LCR_WLEN7 ; 
 int LCR_WLEN8 ; 
 int /*<<< orphan*/  __uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
uart_mu_param(struct uart_bas *bas, int baudrate, int databits, int stopbits,
    int parity)
{
	uint32_t line;
	uint32_t baud;
	
	/*
	 * Zero all settings to make sure
	 * UART is disabled and not configured
	 */
	line = 0x0;
	__uart_setreg(bas, AUX_MU_CNTL_REG, line);

	/* As I know UART is disabled I can setup the line */
	switch (databits) {
	case 7:
		line |= LCR_WLEN7;
		break;
	case 6:
	case 8:
	default:
		line |= LCR_WLEN8;
		break;
	}

	__uart_setreg(bas, AUX_MU_LCR_REG, line);

	/* See 2.2.1 BCM2835-ARM-Peripherals baudrate */
	if (baudrate != 0) {
		baud = CPU_CLOCK / (8 * baudrate);
		/* XXX	
		 *  baud = cpu_clock() / (8 * baudrate);
		 */
		__uart_setreg(bas, AUX_MU_BAUD_REG, ((uint32_t)(baud & 0xFFFF)));
	}
	
	/* re-enable UART */
	__uart_setreg(bas, AUX_MU_CNTL_REG, CNTL_RXENAB|CNTL_TXENAB);
}