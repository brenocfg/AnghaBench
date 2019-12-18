#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u8 ;
typedef  unsigned long u32 ;
typedef  unsigned long u16 ;
struct TYPE_3__ {unsigned long* gprs; size_t io_gpr; int /*<<< orphan*/  io_pc; int /*<<< orphan*/  pc; } ;
struct kvm_vcpu {int mmio_needed; TYPE_1__ arch; } ;
struct TYPE_4__ {int len; scalar_t__ data; } ;
struct kvm_run {TYPE_2__ mmio; } ;
typedef  unsigned long s8 ;
typedef  unsigned long s64 ;
typedef  unsigned long s32 ;
typedef  unsigned long s16 ;
typedef  enum emulation_result { ____Placeholder_emulation_result } emulation_result ;

/* Variables and functions */
 int EMULATE_DONE ; 
 int EMULATE_FAIL ; 
 int /*<<< orphan*/  kvm_err (char*,int) ; 

enum emulation_result kvm_mips_complete_mmio_load(struct kvm_vcpu *vcpu,
						  struct kvm_run *run)
{
	unsigned long *gpr = &vcpu->arch.gprs[vcpu->arch.io_gpr];
	enum emulation_result er = EMULATE_DONE;

	if (run->mmio.len > sizeof(*gpr)) {
		kvm_err("Bad MMIO length: %d", run->mmio.len);
		er = EMULATE_FAIL;
		goto done;
	}

	/* Restore saved resume PC */
	vcpu->arch.pc = vcpu->arch.io_pc;

	switch (run->mmio.len) {
	case 8:
		*gpr = *(s64 *)run->mmio.data;
		break;

	case 4:
		if (vcpu->mmio_needed == 2)
			*gpr = *(s32 *)run->mmio.data;
		else
			*gpr = *(u32 *)run->mmio.data;
		break;

	case 2:
		if (vcpu->mmio_needed == 2)
			*gpr = *(s16 *) run->mmio.data;
		else
			*gpr = *(u16 *)run->mmio.data;

		break;
	case 1:
		if (vcpu->mmio_needed == 2)
			*gpr = *(s8 *) run->mmio.data;
		else
			*gpr = *(u8 *) run->mmio.data;
		break;
	}

done:
	return er;
}