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
typedef  int /*<<< orphan*/  uint32_t ;
struct uart_bas {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNC_UART_MODE_REG ; 
 int /*<<< orphan*/  CDNC_UART_MODE_REG_6BIT ; 
 int /*<<< orphan*/  CDNC_UART_MODE_REG_7BIT ; 
 int /*<<< orphan*/  CDNC_UART_MODE_REG_8BIT ; 
 int /*<<< orphan*/  CDNC_UART_MODE_REG_PAR_EVEN ; 
 int /*<<< orphan*/  CDNC_UART_MODE_REG_PAR_MARK ; 
 int /*<<< orphan*/  CDNC_UART_MODE_REG_PAR_NONE ; 
 int /*<<< orphan*/  CDNC_UART_MODE_REG_PAR_ODD ; 
 int /*<<< orphan*/  CDNC_UART_MODE_REG_PAR_SPACE ; 
 int /*<<< orphan*/  CDNC_UART_MODE_REG_STOP2 ; 
 int EINVAL ; 
#define  UART_PARITY_EVEN 132 
#define  UART_PARITY_MARK 131 
#define  UART_PARITY_NONE 130 
#define  UART_PARITY_ODD 129 
#define  UART_PARITY_SPACE 128 
 int /*<<< orphan*/  WR4 (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cdnc_uart_set_baud (struct uart_bas*,int) ; 

__attribute__((used)) static int
cdnc_uart_set_params(struct uart_bas *bas, int baudrate, int databits,
		      int stopbits, int parity)
{
	uint32_t mode_reg_value = 0;

	switch (databits) {
	case 6:
		mode_reg_value |= CDNC_UART_MODE_REG_6BIT;
		break;
	case 7:
		mode_reg_value |= CDNC_UART_MODE_REG_7BIT;
		break;
	case 8:
	default:
		mode_reg_value |= CDNC_UART_MODE_REG_8BIT;
		break;
	}

	if (stopbits == 2)
		mode_reg_value |= CDNC_UART_MODE_REG_STOP2;

	switch (parity) {
	case UART_PARITY_MARK:
		mode_reg_value |= CDNC_UART_MODE_REG_PAR_MARK;
		break;
	case UART_PARITY_SPACE:
		mode_reg_value |= CDNC_UART_MODE_REG_PAR_SPACE;
		break;
	case UART_PARITY_ODD:
		mode_reg_value |= CDNC_UART_MODE_REG_PAR_ODD;
		break;
	case UART_PARITY_EVEN:
		mode_reg_value |= CDNC_UART_MODE_REG_PAR_EVEN;
		break;
	case UART_PARITY_NONE:
	default:
		mode_reg_value |= CDNC_UART_MODE_REG_PAR_NONE;
		break;		
	}

	WR4(bas, CDNC_UART_MODE_REG, mode_reg_value);

	if (baudrate > 0 && cdnc_uart_set_baud(bas, baudrate) < 0)
		return (EINVAL);

	return(0);
}