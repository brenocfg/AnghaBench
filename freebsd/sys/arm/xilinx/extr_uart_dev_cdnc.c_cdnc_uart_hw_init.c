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
 int /*<<< orphan*/  CDNC_UART_CTRL_REG ; 
 int CDNC_UART_CTRL_REG_RXRST ; 
 int CDNC_UART_CTRL_REG_RX_EN ; 
 int CDNC_UART_CTRL_REG_STOPBRK ; 
 int CDNC_UART_CTRL_REG_TORST ; 
 int CDNC_UART_CTRL_REG_TXRST ; 
 int CDNC_UART_CTRL_REG_TX_EN ; 
 int /*<<< orphan*/  CDNC_UART_IDIS_REG ; 
 int CDNC_UART_INT_ALL ; 
 int /*<<< orphan*/  CDNC_UART_ISTAT_REG ; 
 int /*<<< orphan*/  CDNC_UART_MODEM_CTRL_REG ; 
 int CDNC_UART_MODEM_CTRL_REG_DTR ; 
 int CDNC_UART_MODEM_CTRL_REG_RTS ; 
 int /*<<< orphan*/  CDNC_UART_MODEM_STAT_REG ; 
 int CDNC_UART_MODEM_STAT_REG_DCTS ; 
 int CDNC_UART_MODEM_STAT_REG_DDCD ; 
 int CDNC_UART_MODEM_STAT_REG_DDSR ; 
 int CDNC_UART_MODEM_STAT_REG_TERI ; 
 int /*<<< orphan*/  CDNC_UART_RX_TIMEO_REG ; 
 int /*<<< orphan*/  CDNC_UART_RX_WATER_REG ; 
 int /*<<< orphan*/  CDNC_UART_TX_WATER_REG ; 
 int UART_FIFO_SIZE ; 
 int /*<<< orphan*/  WR4 (struct uart_bas*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cdnc_uart_hw_init(struct uart_bas *bas)
{

	/* Reset RX and TX. */
	WR4(bas, CDNC_UART_CTRL_REG,
	    CDNC_UART_CTRL_REG_RXRST | CDNC_UART_CTRL_REG_TXRST);

	/* Interrupts all off. */
	WR4(bas, CDNC_UART_IDIS_REG, CDNC_UART_INT_ALL);
	WR4(bas, CDNC_UART_ISTAT_REG, CDNC_UART_INT_ALL);

	/* Clear delta bits. */
	WR4(bas, CDNC_UART_MODEM_STAT_REG,
	    CDNC_UART_MODEM_STAT_REG_DDCD | CDNC_UART_MODEM_STAT_REG_TERI |
	    CDNC_UART_MODEM_STAT_REG_DDSR | CDNC_UART_MODEM_STAT_REG_DCTS);

	/* RX FIFO water level, stale timeout */
	WR4(bas, CDNC_UART_RX_WATER_REG, UART_FIFO_SIZE/2);
	WR4(bas, CDNC_UART_RX_TIMEO_REG, 10);

	/* TX FIFO water level (not used.) */
	WR4(bas, CDNC_UART_TX_WATER_REG, UART_FIFO_SIZE/2);

	/* Bring RX and TX online. */
	WR4(bas, CDNC_UART_CTRL_REG,
	    CDNC_UART_CTRL_REG_RX_EN | CDNC_UART_CTRL_REG_TX_EN |
	    CDNC_UART_CTRL_REG_TORST | CDNC_UART_CTRL_REG_STOPBRK);

	/* Set DTR and RTS. */
	WR4(bas, CDNC_UART_MODEM_CTRL_REG, CDNC_UART_MODEM_CTRL_REG_DTR |
	    CDNC_UART_MODEM_CTRL_REG_RTS);
}