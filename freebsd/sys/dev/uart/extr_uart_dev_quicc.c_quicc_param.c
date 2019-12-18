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
typedef  int uint16_t ;
struct uart_bas {scalar_t__ chan; int /*<<< orphan*/  rclk; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  QUICC_REG_BRG (scalar_t__) ; 
 int /*<<< orphan*/  QUICC_REG_SCC_PSMR (scalar_t__) ; 
#define  UART_PARITY_EVEN 132 
#define  UART_PARITY_MARK 131 
#define  UART_PARITY_NONE 130 
#define  UART_PARITY_ODD 129 
#define  UART_PARITY_SPACE 128 
 int quicc_divisor (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  quicc_write2 (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  quicc_write4 (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
quicc_param(struct uart_bas *bas, int baudrate, int databits, int stopbits,
    int parity)
{
	int divisor;
	uint16_t psmr;

	if (baudrate > 0) {
		divisor = quicc_divisor(bas->rclk, baudrate);
		if (divisor == -1)
			return (EINVAL);
		quicc_write4(bas, QUICC_REG_BRG(bas->chan - 1),
		    divisor | 0x10000);
	}

	psmr = 0;
	switch (databits) {
	case 5:		psmr |= 0x0000; break;
	case 6:		psmr |= 0x1000; break;
	case 7:		psmr |= 0x2000; break;
	case 8:		psmr |= 0x3000; break;
	default:	return (EINVAL);
	}
	switch (stopbits) {
	case 1:		psmr |= 0x0000; break;
	case 2:		psmr |= 0x4000; break;
	default:	return (EINVAL);
	}
	switch (parity) {
	case UART_PARITY_EVEN:	psmr |= 0x1a; break;
	case UART_PARITY_MARK:	psmr |= 0x1f; break;
	case UART_PARITY_NONE:	psmr |= 0x00; break;
	case UART_PARITY_ODD:	psmr |= 0x10; break;
	case UART_PARITY_SPACE:	psmr |= 0x15; break;
	default:		return (EINVAL);
	}
	quicc_write2(bas, QUICC_REG_SCC_PSMR(bas->chan - 1), psmr);
	return (0);
}