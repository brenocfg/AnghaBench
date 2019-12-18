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
struct uart_bas {int /*<<< orphan*/  rclk; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SSCOM_UBRDIV ; 
 int /*<<< orphan*/  SSCOM_ULCON ; 
#define  UART_PARITY_EVEN 132 
#define  UART_PARITY_MARK 131 
#define  UART_PARITY_NONE 130 
#define  UART_PARITY_ODD 129 
#define  UART_PARITY_SPACE 128 
 int ULCON_LENGTH_5 ; 
 int ULCON_LENGTH_6 ; 
 int ULCON_LENGTH_7 ; 
 int ULCON_LENGTH_8 ; 
 int ULCON_PARITY_EVEN ; 
 int ULCON_PARITY_NONE ; 
 int ULCON_PARITY_ODD ; 
 int ULCON_STOP ; 
 int sscomspeed (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
exynos4210_uart_param(struct uart_bas *bas, int baudrate, int databits,
    int stopbits, int parity)
{
	int brd, ulcon;

	ulcon = 0;

	switch(databits) {
	case 5:
		ulcon |= ULCON_LENGTH_5;
		break;
	case 6:
		ulcon |= ULCON_LENGTH_6;
		break;
	case 7:
		ulcon |= ULCON_LENGTH_7;
		break;
	case 8:
		ulcon |= ULCON_LENGTH_8;
		break;
	default:
		return (EINVAL);
	}

	switch (parity) {
	case UART_PARITY_NONE:
		ulcon |= ULCON_PARITY_NONE;
		break;
	case UART_PARITY_ODD:
		ulcon |= ULCON_PARITY_ODD;
		break;
	case UART_PARITY_EVEN:
		ulcon |= ULCON_PARITY_EVEN;
		break;
	case UART_PARITY_MARK:
	case UART_PARITY_SPACE:
	default:
		return (EINVAL);
	}

	if (stopbits == 2)
		ulcon |= ULCON_STOP;

	uart_setreg(bas, SSCOM_ULCON, ulcon);

	brd = sscomspeed(baudrate, bas->rclk);
	uart_setreg(bas, SSCOM_UBRDIV, brd);

	return (0);
}