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
typedef  scalar_t__ u32 ;
struct clock_event_device {int dummy; } ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {unsigned int num; } ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  HPET_COUNTER ; 
 scalar_t__ HPET_MIN_CYCLES ; 
 int /*<<< orphan*/  HPET_Tn_CMP (unsigned int) ; 
 TYPE_1__* clockevent_to_channel (struct clock_event_device*) ; 
 scalar_t__ hpet_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpet_writel (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hpet_clkevt_set_next_event(unsigned long delta, struct clock_event_device *evt)
{
	unsigned int channel = clockevent_to_channel(evt)->num;
	u32 cnt;
	s32 res;

	cnt = hpet_readl(HPET_COUNTER);
	cnt += (u32) delta;
	hpet_writel(cnt, HPET_Tn_CMP(channel));

	/*
	 * HPETs are a complete disaster. The compare register is
	 * based on a equal comparison and neither provides a less
	 * than or equal functionality (which would require to take
	 * the wraparound into account) nor a simple count down event
	 * mode. Further the write to the comparator register is
	 * delayed internally up to two HPET clock cycles in certain
	 * chipsets (ATI, ICH9,10). Some newer AMD chipsets have even
	 * longer delays. We worked around that by reading back the
	 * compare register, but that required another workaround for
	 * ICH9,10 chips where the first readout after write can
	 * return the old stale value. We already had a minimum
	 * programming delta of 5us enforced, but a NMI or SMI hitting
	 * between the counter readout and the comparator write can
	 * move us behind that point easily. Now instead of reading
	 * the compare register back several times, we make the ETIME
	 * decision based on the following: Return ETIME if the
	 * counter value after the write is less than HPET_MIN_CYCLES
	 * away from the event or if the counter is already ahead of
	 * the event. The minimum programming delta for the generic
	 * clockevents code is set to 1.5 * HPET_MIN_CYCLES.
	 */
	res = (s32)(cnt - hpet_readl(HPET_COUNTER));

	return res < HPET_MIN_CYCLES ? -ETIME : 0;
}