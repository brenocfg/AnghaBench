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
typedef  int u64 ;
struct clocksource {int dummy; } ;

/* Variables and functions */
 scalar_t__ HW_TIMROT_TIMCOUNTn (int) ; 
 int __raw_readl (scalar_t__) ; 
 scalar_t__ mxs_timrot_base ; 

__attribute__((used)) static u64 timrotv1_get_cycles(struct clocksource *cs)
{
	return ~((__raw_readl(mxs_timrot_base + HW_TIMROT_TIMCOUNTn(1))
			& 0xffff0000) >> 16);
}