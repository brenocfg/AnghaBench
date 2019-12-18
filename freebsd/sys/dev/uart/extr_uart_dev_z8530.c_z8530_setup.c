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
typedef  int uint8_t ;
struct uart_bas {scalar_t__ rclk; int chan; } ;

/* Variables and functions */
 int CMC_RC_BRG ; 
 int CMC_TC_BRG ; 
 scalar_t__ DEFAULT_RCLK ; 
 int MCB1_NRZ ; 
 int MIC_CRA ; 
 int MIC_CRB ; 
 int MIC_NV ; 
 int TPC_DTR ; 
 int TPC_RTS ; 
 int UART_PCLK ; 
 int /*<<< orphan*/  WR_CMC ; 
 int /*<<< orphan*/  WR_MCB1 ; 
 int /*<<< orphan*/  WR_MCB2 ; 
 int /*<<< orphan*/  WR_MIC ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_setmreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  z8530_param (struct uart_bas*,int,int,int,int,int*) ; 

__attribute__((used)) static int
z8530_setup(struct uart_bas *bas, int baudrate, int databits, int stopbits,
    int parity)
{
	uint8_t tpc;

	if (bas->rclk == 0)
		bas->rclk = DEFAULT_RCLK;

	/* Assume we don't need to perform a full hardware reset. */
	switch (bas->chan) {
	case 1:
		uart_setmreg(bas, WR_MIC, MIC_NV | MIC_CRA);
		break;
	case 2:
		uart_setmreg(bas, WR_MIC, MIC_NV | MIC_CRB);
		break;
	}
	uart_barrier(bas);
	/* Set clock sources. */
	uart_setmreg(bas, WR_CMC, CMC_RC_BRG | CMC_TC_BRG);
	uart_setmreg(bas, WR_MCB2, UART_PCLK);
	uart_barrier(bas);
	/* Set data encoding. */
	uart_setmreg(bas, WR_MCB1, MCB1_NRZ);
	uart_barrier(bas);

	tpc = TPC_DTR | TPC_RTS;
	z8530_param(bas, baudrate, databits, stopbits, parity, &tpc);
	return (int)tpc;
}