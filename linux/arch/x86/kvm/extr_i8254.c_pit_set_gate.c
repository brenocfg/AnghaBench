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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {struct kvm_kpit_channel_state* channels; } ;
struct kvm_pit {TYPE_1__ pit_state; } ;
struct kvm_kpit_channel_state {int mode; int /*<<< orphan*/  gate; int /*<<< orphan*/  count_load_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get () ; 

__attribute__((used)) static void pit_set_gate(struct kvm_pit *pit, int channel, u32 val)
{
	struct kvm_kpit_channel_state *c = &pit->pit_state.channels[channel];

	switch (c->mode) {
	default:
	case 0:
	case 4:
		/* XXX: just disable/enable counting */
		break;
	case 1:
	case 2:
	case 3:
	case 5:
		/* Restart counting on rising edge. */
		if (c->gate < val)
			c->count_load_time = ktime_get();
		break;
	}

	c->gate = val;
}