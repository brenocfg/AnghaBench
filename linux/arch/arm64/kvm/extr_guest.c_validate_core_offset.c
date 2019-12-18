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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {int dummy; } ;
struct kvm_one_reg {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 int KVM_REG_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_reg_offset_from_id (int /*<<< orphan*/ ) ; 
 int core_reg_size_from_offset (struct kvm_vcpu const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int validate_core_offset(const struct kvm_vcpu *vcpu,
				const struct kvm_one_reg *reg)
{
	u64 off = core_reg_offset_from_id(reg->id);
	int size = core_reg_size_from_offset(vcpu, off);

	if (size < 0)
		return -EINVAL;

	if (KVM_REG_SIZE(reg->id) != size)
		return -EINVAL;

	return 0;
}