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
 int /*<<< orphan*/  SETREG (struct uart_bas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_DM_CR ; 
 int UART_DM_CR_RX_ENABLE ; 
 int UART_DM_CR_TX_ENABLE ; 
 int /*<<< orphan*/  UART_DM_DMEN ; 
 int UART_DM_DMEN_RX_SC_ENABLE ; 
 int /*<<< orphan*/  UART_DM_HCR ; 
 int /*<<< orphan*/  UART_DM_IMR ; 
 int /*<<< orphan*/  UART_DM_IPR ; 
 int /*<<< orphan*/  UART_DM_IRDA ; 
 int /*<<< orphan*/  UART_DM_MR1 ; 
 int /*<<< orphan*/  UART_DM_RESET_BREAK_INT ; 
 int /*<<< orphan*/  UART_DM_RESET_ERROR_STATUS ; 
 int /*<<< orphan*/  UART_DM_RESET_RX ; 
 int /*<<< orphan*/  UART_DM_RESET_STALE_INT ; 
 int /*<<< orphan*/  UART_DM_RESET_TX ; 
 int /*<<< orphan*/  UART_DM_RFWR ; 
 int UART_DM_RFW_VALUE ; 
 int UART_DM_STALE_TIMEOUT_LSB ; 
 int /*<<< orphan*/  UART_DM_TFWR ; 
 int UART_DM_TFW_VALUE ; 
 int /*<<< orphan*/  msm_uart_param (struct uart_bas*,int,int,int,int) ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_setreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
msm_init(struct uart_bas *bas, int baudrate, int databits, int stopbits,
    int parity)
{

	if (bas->rclk == 0)
		bas->rclk = DEF_CLK;

	KASSERT(bas->rclk != 0, ("msm_init: Invalid rclk"));

	/* Set default parameters */
	msm_uart_param(bas, baudrate, databits, stopbits, parity);

	/*
	 * Configure UART mode registers MR1 and MR2.
	 * Hardware flow control isn't supported.
	 */
	uart_setreg(bas, UART_DM_MR1, 0x0);

	/* Reset interrupt mask register. */
	uart_setreg(bas, UART_DM_IMR, 0);

	/*
	 * Configure Tx and Rx watermarks configuration registers.
	 * TX watermark value is set to 0 - interrupt is generated when
	 * FIFO level is less than or equal to 0.
	 */
	uart_setreg(bas, UART_DM_TFWR, UART_DM_TFW_VALUE);

	/* Set RX watermark value */
	uart_setreg(bas, UART_DM_RFWR, UART_DM_RFW_VALUE);

	/*
	 * Configure Interrupt Programming Register.
	 * Set initial Stale timeout value.
	 */
	uart_setreg(bas, UART_DM_IPR, UART_DM_STALE_TIMEOUT_LSB);

	/* Disable IRDA mode */
	uart_setreg(bas, UART_DM_IRDA, 0x0);

	/*
	 * Configure and enable sim interface if required.
	 * Configure hunt character value in HCR register.
	 * Keep it in reset state.
	 */
	uart_setreg(bas, UART_DM_HCR, 0x0);

	/* Issue soft reset command */
	SETREG(bas, UART_DM_CR, UART_DM_RESET_TX);
	SETREG(bas, UART_DM_CR, UART_DM_RESET_RX);
	SETREG(bas, UART_DM_CR, UART_DM_RESET_ERROR_STATUS);
	SETREG(bas, UART_DM_CR, UART_DM_RESET_BREAK_INT);
	SETREG(bas, UART_DM_CR, UART_DM_RESET_STALE_INT);

	/* Enable/Disable Rx/Tx DM interfaces */
	uart_setreg(bas, UART_DM_DMEN, UART_DM_DMEN_RX_SC_ENABLE);

	/* Enable transmitter and receiver */
	uart_setreg(bas, UART_DM_CR, UART_DM_CR_RX_ENABLE);
	uart_setreg(bas, UART_DM_CR, UART_DM_CR_TX_ENABLE);

	uart_barrier(bas);
}