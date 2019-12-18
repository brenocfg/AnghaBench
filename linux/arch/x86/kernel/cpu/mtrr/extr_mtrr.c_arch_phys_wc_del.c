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
 int MTRR_TO_PHYS_WC_OFFSET ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mtrr_del (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void arch_phys_wc_del(int handle)
{
	if (handle >= 1) {
		WARN_ON(handle < MTRR_TO_PHYS_WC_OFFSET);
		mtrr_del(handle - MTRR_TO_PHYS_WC_OFFSET, 0, 0);
	}
}