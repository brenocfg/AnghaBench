#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct clock_event_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 unsigned long BM_C0_EN ; 
 scalar_t__ HW_MR0 ; 
 scalar_t__ HW_TCR ; 
 scalar_t__ SET_REG ; 
 TYPE_1__ priv ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,scalar_t__) ; 

__attribute__((used)) static int asm9260_timer_set_next_event(unsigned long delta,
					 struct clock_event_device *evt)
{
	/* configure match count for TC0 */
	writel_relaxed(delta, priv.base + HW_MR0);
	/* enable TC0 */
	writel_relaxed(BM_C0_EN, priv.base + HW_TCR + SET_REG);
	return 0;
}