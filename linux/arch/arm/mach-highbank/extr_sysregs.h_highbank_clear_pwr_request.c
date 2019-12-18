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
 scalar_t__ HB_SREG_A9_PWR_REQ ; 
 int /*<<< orphan*/  highbank_clear_core_pwr () ; 
 scalar_t__ sregs_base ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static inline void highbank_clear_pwr_request(void)
{
	writel(~0UL, sregs_base + HB_SREG_A9_PWR_REQ);
	highbank_clear_core_pwr();
}