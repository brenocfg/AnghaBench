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
 int /*<<< orphan*/  RIC_FLUSH_ALL ; 
 int /*<<< orphan*/  _tlbie_pid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tlbiel_kernel_broadcast () ; 
 scalar_t__ cputlb_use_tlbie () ; 

void radix__flush_tlb_kernel_range(unsigned long start, unsigned long end)
{
	if (cputlb_use_tlbie())
		_tlbie_pid(0, RIC_FLUSH_ALL);
	else
		_tlbiel_kernel_broadcast();
}