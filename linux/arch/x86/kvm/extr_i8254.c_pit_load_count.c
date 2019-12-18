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
typedef  int u32 ;
struct kvm_kpit_state {TYPE_1__* channels; } ;
struct kvm_pit {struct kvm_kpit_state pit_state; } ;
struct TYPE_2__ {int count; int mode; int /*<<< orphan*/  count_load_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  create_pit_timer (struct kvm_pit*,int,int) ; 
 int /*<<< orphan*/  destroy_pit_timer (struct kvm_pit*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 

__attribute__((used)) static void pit_load_count(struct kvm_pit *pit, int channel, u32 val)
{
	struct kvm_kpit_state *ps = &pit->pit_state;

	pr_debug("load_count val is %d, channel is %d\n", val, channel);

	/*
	 * The largest possible initial count is 0; this is equivalent
	 * to 216 for binary counting and 104 for BCD counting.
	 */
	if (val == 0)
		val = 0x10000;

	ps->channels[channel].count = val;

	if (channel != 0) {
		ps->channels[channel].count_load_time = ktime_get();
		return;
	}

	/* Two types of timer
	 * mode 1 is one shot, mode 2 is period, otherwise del timer */
	switch (ps->channels[0].mode) {
	case 0:
	case 1:
        /* FIXME: enhance mode 4 precision */
	case 4:
		create_pit_timer(pit, val, 0);
		break;
	case 2:
	case 3:
		create_pit_timer(pit, val, 1);
		break;
	default:
		destroy_pit_timer(pit);
	}
}