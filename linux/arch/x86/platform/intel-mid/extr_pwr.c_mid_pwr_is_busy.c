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
struct mid_pwr {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ PM_STS ; 
 int PM_STS_BUSY ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static bool mid_pwr_is_busy(struct mid_pwr *pwr)
{
	return !!(readl(pwr->regs + PM_STS) & PM_STS_BUSY);
}