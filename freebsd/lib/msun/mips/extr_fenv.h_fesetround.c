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
typedef  int fexcept_t ;

/* Variables and functions */
 int _ROUND_MASK ; 
 int /*<<< orphan*/  __cfc1 (int) ; 
 int /*<<< orphan*/  __ctc1 (int) ; 

inline int
fesetround(int __round)
{
	fexcept_t fcsr;

	if (__round & ~_ROUND_MASK)
		return (-1);

	__cfc1(fcsr);
	fcsr &= ~_ROUND_MASK;
	fcsr |= __round;
	__ctc1(fcsr);

	return (0);
}