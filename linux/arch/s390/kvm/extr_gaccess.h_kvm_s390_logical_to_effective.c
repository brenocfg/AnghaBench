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
struct TYPE_5__ {TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
typedef  int /*<<< orphan*/  psw_t ;
struct TYPE_6__ {scalar_t__ eaba; } ;
struct TYPE_4__ {int /*<<< orphan*/  gpsw; } ;

/* Variables and functions */
 scalar_t__ PSW_BITS_AMODE_31BIT ; 
 scalar_t__ PSW_BITS_AMODE_64BIT ; 
 TYPE_3__ psw_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned long kvm_s390_logical_to_effective(struct kvm_vcpu *vcpu,
							  unsigned long ga)
{
	psw_t *psw = &vcpu->arch.sie_block->gpsw;

	if (psw_bits(*psw).eaba == PSW_BITS_AMODE_64BIT)
		return ga;
	if (psw_bits(*psw).eaba == PSW_BITS_AMODE_31BIT)
		return ga & ((1UL << 31) - 1);
	return ga & ((1UL << 24) - 1);
}