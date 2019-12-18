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
struct uart_bas {scalar_t__ rclk; } ;

/* Variables and functions */
 scalar_t__ DEF_CLK ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SSCOM_UCON ; 
 int /*<<< orphan*/  SSCOM_UFCON ; 
 int /*<<< orphan*/  SSCOM_UMCON ; 
 int UCON_RXMODE_INT ; 
 int UCON_TOINT ; 
 int UCON_TXMODE_INT ; 
 int UFCON_FIFO_ENABLE ; 
 int UFCON_RXFIFO_RESET ; 
 int UFCON_RXTRIGGER_8 ; 
 int UFCON_TXFIFO_RESET ; 
 int UFCON_TXTRIGGER_8 ; 
 int UMCON_RTS ; 
 int /*<<< orphan*/  exynos4210_uart_param (struct uart_bas*,int,int,int,int) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
exynos4210_init(struct uart_bas *bas, int baudrate, int databits, int stopbits,
    int parity)
{

	if (bas->rclk == 0)
		bas->rclk = DEF_CLK;

	KASSERT(bas->rclk != 0, ("exynos4210_init: Invalid rclk"));

	uart_setreg(bas, SSCOM_UCON, 0);
	uart_setreg(bas, SSCOM_UFCON,
	    UFCON_TXTRIGGER_8 | UFCON_RXTRIGGER_8 |
	    UFCON_TXFIFO_RESET | UFCON_RXFIFO_RESET |
	    UFCON_FIFO_ENABLE);
	exynos4210_uart_param(bas, baudrate, databits, stopbits, parity);

	/* Enable UART. */
	uart_setreg(bas, SSCOM_UCON, UCON_TXMODE_INT | UCON_RXMODE_INT |
	    UCON_TOINT);
	uart_setreg(bas, SSCOM_UMCON, UMCON_RTS);
}