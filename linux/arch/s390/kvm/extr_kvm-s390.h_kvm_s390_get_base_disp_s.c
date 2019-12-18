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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_8__ {TYPE_2__* sie_block; } ;
struct kvm_vcpu {TYPE_1__* run; TYPE_3__ arch; } ;
struct TYPE_10__ {int /*<<< orphan*/ * gprs; } ;
struct TYPE_9__ {TYPE_5__ regs; } ;
struct TYPE_7__ {int ipb; } ;
struct TYPE_6__ {TYPE_4__ s; } ;

/* Variables and functions */

__attribute__((used)) static inline u64 kvm_s390_get_base_disp_s(struct kvm_vcpu *vcpu, u8 *ar)
{
	u32 base2 = vcpu->arch.sie_block->ipb >> 28;
	u32 disp2 = ((vcpu->arch.sie_block->ipb & 0x0fff0000) >> 16);

	if (ar)
		*ar = base2;

	return (base2 ? vcpu->run->s.regs.gprs[base2] : 0) + disp2;
}