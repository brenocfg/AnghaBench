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
struct TYPE_2__ {struct kvm_kpit_channel_state* channels; } ;
struct kvm_pit {TYPE_1__ pit_state; } ;
struct kvm_kpit_channel_state {int status_latched; int status; int rw_mode; int mode; int bcd; } ;

/* Variables and functions */
 int pit_get_out (struct kvm_pit*,int) ; 

__attribute__((used)) static void pit_latch_status(struct kvm_pit *pit, int channel)
{
	struct kvm_kpit_channel_state *c = &pit->pit_state.channels[channel];

	if (!c->status_latched) {
		/* TODO: Return NULL COUNT (bit 6). */
		c->status = ((pit_get_out(pit, channel) << 7) |
				(c->rw_mode << 4) |
				(c->mode << 1) |
				c->bcd);
		c->status_latched = 1;
	}
}