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
 scalar_t__ PM_ICS ; 
 int /*<<< orphan*/  PM_ICS_IE ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mid_pwr_interrupt_disable(struct mid_pwr *pwr)
{
	writel(~PM_ICS_IE, pwr->regs + PM_ICS);
}