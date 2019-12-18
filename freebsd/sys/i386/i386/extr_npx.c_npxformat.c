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
 int _MC_FPFMT_387 ; 
 int _MC_FPFMT_NODEV ; 
 int _MC_FPFMT_XMM ; 
 scalar_t__ cpu_fxsr ; 
 int /*<<< orphan*/  hw_float ; 

int
npxformat(void)
{

	if (!hw_float)
		return (_MC_FPFMT_NODEV);
	if (cpu_fxsr)
		return (_MC_FPFMT_XMM);
	return (_MC_FPFMT_387);
}