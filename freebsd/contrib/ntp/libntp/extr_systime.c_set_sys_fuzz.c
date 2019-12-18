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
 int /*<<< orphan*/  INSIST (int) ; 
 scalar_t__ ceil (double) ; 
 double sys_fuzz ; 
 long sys_fuzz_nsec ; 

void
set_sys_fuzz(
	double	fuzz_val
	)
{
	sys_fuzz = fuzz_val;
	INSIST(sys_fuzz >= 0);
	INSIST(sys_fuzz <= 1.0);
	/* [Bug 3450] ensure nsec fuzz >= sys_fuzz to reduce chance of
	 * short-falling fuzz advance
	 */
	sys_fuzz_nsec = (long)ceil(sys_fuzz * 1e9);
}