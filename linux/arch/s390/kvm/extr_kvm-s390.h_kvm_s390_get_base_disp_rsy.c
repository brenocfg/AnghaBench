#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  long u64 ;
typedef  int u32 ;
struct TYPE_10__ {TYPE_4__* sie_block; } ;
struct kvm_vcpu {TYPE_3__* run; TYPE_5__ arch; } ;
struct TYPE_9__ {int ipb; } ;
struct TYPE_6__ {long* gprs; } ;
struct TYPE_7__ {TYPE_1__ regs; } ;
struct TYPE_8__ {TYPE_2__ s; } ;

/* Variables and functions */

__attribute__((used)) static inline u64 kvm_s390_get_base_disp_rsy(struct kvm_vcpu *vcpu, u8 *ar)
{
	u32 base2 = vcpu->arch.sie_block->ipb >> 28;
	u32 disp2 = ((vcpu->arch.sie_block->ipb & 0x0fff0000) >> 16) +
			((vcpu->arch.sie_block->ipb & 0xff00) << 4);
	/* The displacement is a 20bit _SIGNED_ value */
	if (disp2 & 0x80000)
		disp2+=0xfff00000;

	if (ar)
		*ar = base2;

	return (base2 ? vcpu->run->s.regs.gprs[base2] : 0) + (long)(int)disp2;
}