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
struct uart_bas {int dummy; } ;

/* Variables and functions */
 int IIR_BUSY ; 
 int IIR_IMASK ; 
 int IIR_MLSC ; 
 int IIR_NOPEND ; 
 int IIR_RLS ; 
 int IIR_RXRDY ; 
 int IIR_RXTOUT ; 
 int /*<<< orphan*/  REG_DATA ; 
 int /*<<< orphan*/  REG_IIR ; 
 int /*<<< orphan*/  REG_LSR ; 
 int /*<<< orphan*/  REG_MSR ; 
 int /*<<< orphan*/  REG_USR ; 
 int /*<<< orphan*/  uart_barrier (struct uart_bas*) ; 
 int uart_getreg (struct uart_bas*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
oct16550_clrint (struct uart_bas *bas)
{
	uint8_t iir;

	iir = uart_getreg(bas, REG_IIR);
	while ((iir & IIR_NOPEND) == 0) {
		iir &= IIR_IMASK;
		if (iir == IIR_RLS)
			(void)uart_getreg(bas, REG_LSR);
		else if (iir == IIR_RXRDY || iir == IIR_RXTOUT)
			(void)uart_getreg(bas, REG_DATA);
		else if (iir == IIR_MLSC)
			(void)uart_getreg(bas, REG_MSR);
                else if (iir == IIR_BUSY)
                    	(void) uart_getreg(bas, REG_USR);
		uart_barrier(bas);
		iir = uart_getreg(bas, REG_IIR);
	}
}