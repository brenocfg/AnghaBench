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

/* Variables and functions */
 int MCR_DTR ; 
 int MCR_LOOPBACK ; 
 int MCR_OUT1 ; 
 int MCR_OUT2 ; 
 int MCR_RTS ; 
 int MSR_CTS ; 
 int MSR_DCD ; 
 int MSR_DELTA_MASK ; 
 int MSR_DSR ; 
 int MSR_RI ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static uint8_t
modem_status(uint8_t mcr)
{
	uint8_t msr;

	if (mcr & MCR_LOOPBACK) {
		/*
		 * In the loopback mode certain bits from the MCR are
		 * reflected back into MSR.
		 */
		msr = 0;
		if (mcr & MCR_RTS)
			msr |= MSR_CTS;
		if (mcr & MCR_DTR)
			msr |= MSR_DSR;
		if (mcr & MCR_OUT1)
			msr |= MSR_RI;
		if (mcr & MCR_OUT2)
			msr |= MSR_DCD;
	} else {
		/*
		 * Always assert DCD and DSR so tty open doesn't block
		 * even if CLOCAL is turned off.
		 */
		msr = MSR_DCD | MSR_DSR;
	}
	assert((msr & MSR_DELTA_MASK) == 0);

	return (msr);
}