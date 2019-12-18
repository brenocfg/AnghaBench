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
struct TYPE_2__ {int ticks_per_jiffy; scalar_t__ base; } ;

/* Variables and functions */
 int BM_C0_EN ; 
 int BM_MCR_RES_EN (int /*<<< orphan*/ ) ; 
 int BM_MCR_STOP_EN (int /*<<< orphan*/ ) ; 
 scalar_t__ CLR_REG ; 
 scalar_t__ HW_MCR ; 
 scalar_t__ HW_MR0 ; 
 scalar_t__ HW_TCR ; 
 scalar_t__ SET_REG ; 
 int /*<<< orphan*/  __asm9260_timer_shutdown (struct clock_event_device*) ; 
 TYPE_1__ priv ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int asm9260_timer_set_periodic(struct clock_event_device *evt)
{
	__asm9260_timer_shutdown(evt);

	/* disable reset and stop on match */
	writel_relaxed(BM_MCR_RES_EN(0) | BM_MCR_STOP_EN(0),
		       priv.base + HW_MCR + CLR_REG);
	/* configure match count for TC0 */
	writel_relaxed(priv.ticks_per_jiffy, priv.base + HW_MR0);
	/* enable TC0 */
	writel_relaxed(BM_C0_EN, priv.base + HW_TCR + SET_REG);
	return 0;
}