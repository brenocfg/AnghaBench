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
typedef  int u32 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int MIPS_GCTL0_GT ; 
 int /*<<< orphan*/  _kvm_vz_restore_htimer (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_vz_should_use_htimer (struct kvm_vcpu*) ; 
 int read_c0_guestctl0 () ; 
 int /*<<< orphan*/  read_gc0_cause () ; 
 int /*<<< orphan*/  read_gc0_compare () ; 
 int /*<<< orphan*/  write_c0_guestctl0 (int) ; 

void kvm_vz_acquire_htimer(struct kvm_vcpu *vcpu)
{
	u32 gctl0;

	gctl0 = read_c0_guestctl0();
	if (!(gctl0 & MIPS_GCTL0_GT) && kvm_vz_should_use_htimer(vcpu)) {
		/* enable guest access to hard timer */
		write_c0_guestctl0(gctl0 | MIPS_GCTL0_GT);

		_kvm_vz_restore_htimer(vcpu, read_gc0_compare(),
				       read_gc0_cause());
	}
}