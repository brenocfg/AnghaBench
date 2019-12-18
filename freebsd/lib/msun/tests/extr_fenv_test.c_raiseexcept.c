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

/* Variables and functions */
 double volatile DBL_MAX ; 
 double DBL_MIN ; 
 int FE_DIVBYZERO ; 
 int FE_INEXACT ; 
 int FE_INVALID ; 
 int FE_OVERFLOW ; 
 int FE_UNDERFLOW ; 

__attribute__((used)) static void
raiseexcept(int excepts)
{
	volatile double d;

	/*
	 * With a compiler that supports the FENV_ACCESS pragma
	 * properly, simple expressions like '0.0 / 0.0' should
	 * be sufficient to generate traps.  Unfortunately, we
	 * need to bring a volatile variable into the equation
	 * to prevent incorrect optimizations.
	 */
	if (excepts & FE_INVALID) {
		d = 0.0;
		d = 0.0 / d;
	}
	if (excepts & FE_DIVBYZERO) {
		d = 0.0;
		d = 1.0 / d;
	}
	if (excepts & FE_OVERFLOW) {
		d = DBL_MAX;
		d *= 2.0;
	}
	if (excepts & FE_UNDERFLOW) {
		d = DBL_MIN;
		d /= DBL_MAX;
	}
	if (excepts & FE_INEXACT) {
		d = DBL_MIN;
		d += 1.0;
	}

	/*
	 * On the x86 (and some other architectures?) the FPU and
	 * integer units are decoupled.  We need to execute an FWAIT
	 * or a floating-point instruction to get synchronous exceptions.
	 */
	d = 1.0;
	d += 1.0;
}