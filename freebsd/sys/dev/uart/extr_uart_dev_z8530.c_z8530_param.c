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
struct uart_bas {int /*<<< orphan*/  rclk; } ;

/* Variables and functions */
 int EINVAL ; 
 int MCB2_BRGE ; 
 int MPM_CM16 ; 
 int MPM_EVEN ; 
 int MPM_PE ; 
 int MPM_SB1 ; 
 int MPM_SB2 ; 
 int RPC_RB5 ; 
 int RPC_RB6 ; 
 int RPC_RB7 ; 
 int RPC_RB8 ; 
 int RPC_RXE ; 
 int TPC_DTR ; 
 int TPC_RTS ; 
 int TPC_TB5 ; 
 int TPC_TB6 ; 
 int TPC_TB7 ; 
 int TPC_TB8 ; 
 int TPC_TXE ; 
#define  UART_PARITY_EVEN 130 
#define  UART_PARITY_NONE 129 
#define  UART_PARITY_ODD 128 
 int UART_PCLK ; 
 int /*<<< orphan*/  WR_MCB2 ; 
 int /*<<< orphan*/  WR_MPM ; 
 int /*<<< orphan*/  WR_RPC ; 
 int /*<<< orphan*/  WR_TCH ; 
 int /*<<< orphan*/  WR_TCL ; 
 int /*<<< orphan*/  WR_TPC ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int /*<<< orphan*/  uart_setmreg (struct uart_bas*,int /*<<< orphan*/ ,int) ; 
 int z8530_divisor (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
z8530_param(struct uart_bas *bas, int baudrate, int databits, int stopbits,
    int parity, uint8_t *tpcp)
{
	int divisor;
	uint8_t mpm, rpc, tpc;

	rpc = RPC_RXE;
	mpm = MPM_CM16;
	tpc = TPC_TXE | (*tpcp & (TPC_DTR | TPC_RTS));

	if (databits >= 8) {
		rpc |= RPC_RB8;
		tpc |= TPC_TB8;
	} else if (databits == 7) {
		rpc |= RPC_RB7;
		tpc |= TPC_TB7;
	} else if (databits == 6) {
		rpc |= RPC_RB6;
		tpc |= TPC_TB6;
	} else {
		rpc |= RPC_RB5;
		tpc |= TPC_TB5;
	}
	mpm |= (stopbits > 1) ? MPM_SB2 : MPM_SB1;
	switch (parity) {
	case UART_PARITY_EVEN:	mpm |= MPM_PE | MPM_EVEN; break;
	case UART_PARITY_NONE:	break;
	case UART_PARITY_ODD:	mpm |= MPM_PE; break;
	default:		return (EINVAL);
	}

	if (baudrate > 0) {
		divisor = z8530_divisor(bas->rclk, baudrate);
		if (divisor == -1)
			return (EINVAL);
	} else
		divisor = -1;

	uart_setmreg(bas, WR_MCB2, UART_PCLK);
	uart_barrier(bas);

	if (divisor >= 0) {
		uart_setmreg(bas, WR_TCL, divisor & 0xff);
		uart_barrier(bas);
		uart_setmreg(bas, WR_TCH, (divisor >> 8) & 0xff);
		uart_barrier(bas);
	}

	uart_setmreg(bas, WR_RPC, rpc);
	uart_barrier(bas);
	uart_setmreg(bas, WR_MPM, mpm);
	uart_barrier(bas);
	uart_setmreg(bas, WR_TPC, tpc);
	uart_barrier(bas);
	uart_setmreg(bas, WR_MCB2, UART_PCLK | MCB2_BRGE);
	uart_barrier(bas);
	*tpcp = tpc;
	return (0);
}