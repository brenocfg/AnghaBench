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
 int /*<<< orphan*/  __mrs_fpsr (int) ; 
 int /*<<< orphan*/  __msr_fpsr (int) ; 

__inline int
feclearexcept(int __excepts)
{
	fexcept_t __r;

	__mrs_fpsr(__r);
	__r &= ~__excepts;
	__msr_fpsr(__r);
	return (0);
}