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
typedef  scalar_t__ u64 ;
struct sve_state_reg_region {scalar_t__ klen; scalar_t__ upad; int /*<<< orphan*/  koffset; } ;
struct TYPE_2__ {int /*<<< orphan*/  sve_max_vl; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_one_reg {unsigned int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ KVM_ARM64_SVE_MAX_SLICES ; 
 scalar_t__ const KVM_REG_ARM64_SVE_FFR (scalar_t__) ; 
 scalar_t__ KVM_REG_ARM64_SVE_PREG (scalar_t__,scalar_t__) ; 
 scalar_t__ KVM_REG_ARM64_SVE_ZREG (scalar_t__,scalar_t__) ; 
 unsigned int KVM_SVE_PREG_SIZE ; 
 unsigned int KVM_SVE_ZREG_SIZE ; 
 scalar_t__ SVE_NUM_PREGS ; 
 scalar_t__ SVE_NUM_SLICES ; 
 scalar_t__ SVE_NUM_ZREGS ; 
 unsigned int SVE_REG_ID_MASK ; 
 unsigned int SVE_REG_ID_SHIFT ; 
 int SVE_REG_SLICE_MASK ; 
 unsigned int SVE_SIG_PREG_OFFSET (unsigned int,unsigned int) ; 
 unsigned int SVE_SIG_PREG_SIZE (unsigned int) ; 
 unsigned int SVE_SIG_REGS_OFFSET ; 
 unsigned int SVE_SIG_ZREG_OFFSET (unsigned int,unsigned int) ; 
 unsigned int SVE_SIG_ZREG_SIZE (unsigned int) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  array_index_nospec (unsigned int,size_t) ; 
 scalar_t__ min (unsigned int,unsigned int) ; 
 unsigned int sve_vq_from_vl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_has_sve (struct kvm_vcpu*) ; 
 size_t vcpu_sve_state_size (struct kvm_vcpu*) ; 

__attribute__((used)) static int sve_reg_to_region(struct sve_state_reg_region *region,
			     struct kvm_vcpu *vcpu,
			     const struct kvm_one_reg *reg)
{
	/* reg ID ranges for Z- registers */
	const u64 zreg_id_min = KVM_REG_ARM64_SVE_ZREG(0, 0);
	const u64 zreg_id_max = KVM_REG_ARM64_SVE_ZREG(SVE_NUM_ZREGS - 1,
						       SVE_NUM_SLICES - 1);

	/* reg ID ranges for P- registers and FFR (which are contiguous) */
	const u64 preg_id_min = KVM_REG_ARM64_SVE_PREG(0, 0);
	const u64 preg_id_max = KVM_REG_ARM64_SVE_FFR(SVE_NUM_SLICES - 1);

	unsigned int vq;
	unsigned int reg_num;

	unsigned int reqoffset, reqlen; /* User-requested offset and length */
	unsigned int maxlen; /* Maxmimum permitted length */

	size_t sve_state_size;

	const u64 last_preg_id = KVM_REG_ARM64_SVE_PREG(SVE_NUM_PREGS - 1,
							SVE_NUM_SLICES - 1);

	/* Verify that the P-regs and FFR really do have contiguous IDs: */
	BUILD_BUG_ON(KVM_REG_ARM64_SVE_FFR(0) != last_preg_id + 1);

	/* Verify that we match the UAPI header: */
	BUILD_BUG_ON(SVE_NUM_SLICES != KVM_ARM64_SVE_MAX_SLICES);

	reg_num = (reg->id & SVE_REG_ID_MASK) >> SVE_REG_ID_SHIFT;

	if (reg->id >= zreg_id_min && reg->id <= zreg_id_max) {
		if (!vcpu_has_sve(vcpu) || (reg->id & SVE_REG_SLICE_MASK) > 0)
			return -ENOENT;

		vq = sve_vq_from_vl(vcpu->arch.sve_max_vl);

		reqoffset = SVE_SIG_ZREG_OFFSET(vq, reg_num) -
				SVE_SIG_REGS_OFFSET;
		reqlen = KVM_SVE_ZREG_SIZE;
		maxlen = SVE_SIG_ZREG_SIZE(vq);
	} else if (reg->id >= preg_id_min && reg->id <= preg_id_max) {
		if (!vcpu_has_sve(vcpu) || (reg->id & SVE_REG_SLICE_MASK) > 0)
			return -ENOENT;

		vq = sve_vq_from_vl(vcpu->arch.sve_max_vl);

		reqoffset = SVE_SIG_PREG_OFFSET(vq, reg_num) -
				SVE_SIG_REGS_OFFSET;
		reqlen = KVM_SVE_PREG_SIZE;
		maxlen = SVE_SIG_PREG_SIZE(vq);
	} else {
		return -EINVAL;
	}

	sve_state_size = vcpu_sve_state_size(vcpu);
	if (WARN_ON(!sve_state_size))
		return -EINVAL;

	region->koffset = array_index_nospec(reqoffset, sve_state_size);
	region->klen = min(maxlen, reqlen);
	region->upad = reqlen - region->klen;

	return 0;
}