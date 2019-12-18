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
typedef  int fenv_t ;

/* Variables and functions */
 int _ROUND_MASK ; 
 int _ROUND_SHIFT ; 
 int /*<<< orphan*/  __stxfsr (int*) ; 

inline int
fegetround(void)
{
	fenv_t __r;

	__stxfsr(&__r);
	return ((__r >> _ROUND_SHIFT) & _ROUND_MASK);
}