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
struct uart_bas {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int UART_DM_5_BPS ; 
 int UART_DM_6_BPS ; 
 int UART_DM_7_BPS ; 
 int UART_DM_8_BPS ; 
 int UART_DM_EVEN_PARITY ; 
 int /*<<< orphan*/  UART_DM_MR2 ; 
 int UART_DM_NO_PARITY ; 
 int UART_DM_ODD_PARITY ; 
 int UART_DM_SBL_1 ; 
 int UART_DM_SBL_2 ; 
 int UART_DM_SPACE_PARITY ; 
#define  UART_PARITY_EVEN 132 
#define  UART_PARITY_MARK 131 
#define  UART_PARITY_NONE 130 
#define  UART_PARITY_ODD 129 
#define  UART_PARITY_SPACE 128 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
msm_uart_param(struct uart_bas *bas, int baudrate, int databits,
    int stopbits, int parity)
{
	int ulcon;

	ulcon = 0;

	switch (databits) {
	case 5:
		ulcon |= (UART_DM_5_BPS << 4);
		break;
	case 6:
		ulcon |= (UART_DM_6_BPS << 4);
		break;
	case 7:
		ulcon |= (UART_DM_7_BPS << 4);
		break;
	case 8:
		ulcon |= (UART_DM_8_BPS << 4);
		break;
	default:
		return (EINVAL);
	}

	switch (parity) {
	case UART_PARITY_NONE:
		ulcon |= UART_DM_NO_PARITY;
		break;
	case UART_PARITY_ODD:
		ulcon |= UART_DM_ODD_PARITY;
		break;
	case UART_PARITY_EVEN:
		ulcon |= UART_DM_EVEN_PARITY;
		break;
	case UART_PARITY_SPACE:
		ulcon |= UART_DM_SPACE_PARITY;
		break;
	case UART_PARITY_MARK:
	default:
		return (EINVAL);
	}

	switch (stopbits) {
	case 1:
		ulcon |= (UART_DM_SBL_1 << 2);
		break;
	case 2:
		ulcon |= (UART_DM_SBL_2 << 2);
		break;
	default:
		return (EINVAL);
	}
	uart_setreg(bas, UART_DM_MR2, ulcon);
	uart_barrier(bas);

	return (0);
}