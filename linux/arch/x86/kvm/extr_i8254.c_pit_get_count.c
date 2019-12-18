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
struct kvm_kpit_channel_state {int mode; int count; } ;
typedef  int s64 ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_PIT_FREQ ; 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 int kpit_elapsed (struct kvm_pit*,struct kvm_kpit_channel_state*,int) ; 
 int mod_64 (int,int) ; 
 int mul_u64_u32_div (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pit_get_count(struct kvm_pit *pit, int channel)
{
	struct kvm_kpit_channel_state *c = &pit->pit_state.channels[channel];
	s64 d, t;
	int counter;

	t = kpit_elapsed(pit, c, channel);
	d = mul_u64_u32_div(t, KVM_PIT_FREQ, NSEC_PER_SEC);

	switch (c->mode) {
	case 0:
	case 1:
	case 4:
	case 5:
		counter = (c->count - d) & 0xffff;
		break;
	case 3:
		/* XXX: may be incorrect for odd counts */
		counter = c->count - (mod_64((2 * d), c->count));
		break;
	default:
		counter = c->count - mod_64(d, c->count);
		break;
	}
	return counter;
}