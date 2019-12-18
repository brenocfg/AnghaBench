#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long ulong ;
struct TYPE_5__ {unsigned long long shadow_fscr; int /*<<< orphan*/  tar; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  tar; } ;
struct TYPE_6__ {TYPE_1__ thread; } ;

/* Variables and functions */
 unsigned long long FSCR_TAR ; 
#define  FSCR_TAR_LG 128 
 int /*<<< orphan*/  SPRN_TAR ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kvmppc_giveup_fac(struct kvm_vcpu *vcpu, ulong fac)
{
#ifdef CONFIG_PPC_BOOK3S_64
	if (!(vcpu->arch.shadow_fscr & (1ULL << fac))) {
		/* Facility not available to the guest, ignore giveup request*/
		return;
	}

	switch (fac) {
	case FSCR_TAR_LG:
		vcpu->arch.tar = mfspr(SPRN_TAR);
		mtspr(SPRN_TAR, current->thread.tar);
		vcpu->arch.shadow_fscr &= ~FSCR_TAR;
		break;
	}
#endif
}