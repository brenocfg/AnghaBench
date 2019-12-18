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
struct TYPE_6__ {TYPE_2__* sie_block; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct TYPE_4__ {unsigned long mask; } ;
struct TYPE_5__ {TYPE_1__ gpsw; } ;

/* Variables and functions */

__attribute__((used)) static inline void kvm_s390_set_psw_cc(struct kvm_vcpu *vcpu, unsigned long cc)
{
	vcpu->arch.sie_block->gpsw.mask &= ~(3UL << 44);
	vcpu->arch.sie_block->gpsw.mask |= cc << 44;
}