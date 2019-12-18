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
 int /*<<< orphan*/  NDS32_SR_INT_PEND ; 
 int __nds32__mfsr (int /*<<< orphan*/ ) ; 
 int wake_mask ; 

__attribute__((used)) static void nds32_suspend_cpu(void)
{
	while (!(__nds32__mfsr(NDS32_SR_INT_PEND) & wake_mask))
		__asm__ volatile ("standby no_wake_grant\n\t");
}