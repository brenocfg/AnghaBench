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
struct kvm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  has_64bscao; int /*<<< orphan*/  has_esca; } ;

/* Variables and functions */
#define  KVM_CAP_ASYNC_PF 161 
#define  KVM_CAP_DEVICE_CTRL 160 
#define  KVM_CAP_ENABLE_CAP 159 
#define  KVM_CAP_IMMEDIATE_EXIT 158 
#define  KVM_CAP_IOEVENTFD 157 
#define  KVM_CAP_MAX_VCPUS 156 
#define  KVM_CAP_MAX_VCPU_ID 155 
#define  KVM_CAP_MP_STATE 154 
#define  KVM_CAP_NR_VCPUS 153 
#define  KVM_CAP_ONE_REG 152 
#define  KVM_CAP_S390_AIS 151 
#define  KVM_CAP_S390_AIS_MIGRATION 150 
#define  KVM_CAP_S390_BPB 149 
#define  KVM_CAP_S390_CMMA_MIGRATION 148 
#define  KVM_CAP_S390_COW 147 
#define  KVM_CAP_S390_CSS_SUPPORT 146 
#define  KVM_CAP_S390_GMAP 145 
#define  KVM_CAP_S390_GS 144 
#define  KVM_CAP_S390_HPAGE_1M 143 
#define  KVM_CAP_S390_INJECT_IRQ 142 
#define  KVM_CAP_S390_IRQCHIP 141 
#define  KVM_CAP_S390_IRQ_STATE 140 
#define  KVM_CAP_S390_MEM_OP 139 
#define  KVM_CAP_S390_PSW 138 
#define  KVM_CAP_S390_RI 137 
#define  KVM_CAP_S390_SKEYS 136 
#define  KVM_CAP_S390_UCONTROL 135 
#define  KVM_CAP_S390_USER_INSTR0 134 
#define  KVM_CAP_S390_USER_SIGP 133 
#define  KVM_CAP_S390_USER_STSI 132 
#define  KVM_CAP_S390_VECTOR_REGISTERS 131 
#define  KVM_CAP_SYNC_MMU 130 
#define  KVM_CAP_SYNC_REGS 129 
#define  KVM_CAP_VM_ATTRIBUTES 128 
 int KVM_MAX_VCPUS ; 
 int KVM_S390_BSCA_CPU_SLOTS ; 
 int KVM_S390_ESCA_CPU_SLOTS ; 
 int MACHINE_HAS_ESOP ; 
 int MACHINE_HAS_VX ; 
 int MEM_OP_MAX_SIZE ; 
 int /*<<< orphan*/  hpage ; 
 int /*<<< orphan*/  kvm_is_ucontrol (struct kvm*) ; 
 int /*<<< orphan*/  kvm_s390_use_sca_entries () ; 
 TYPE_1__ sclp ; 
 int test_facility (int) ; 

int kvm_vm_ioctl_check_extension(struct kvm *kvm, long ext)
{
	int r;

	switch (ext) {
	case KVM_CAP_S390_PSW:
	case KVM_CAP_S390_GMAP:
	case KVM_CAP_SYNC_MMU:
#ifdef CONFIG_KVM_S390_UCONTROL
	case KVM_CAP_S390_UCONTROL:
#endif
	case KVM_CAP_ASYNC_PF:
	case KVM_CAP_SYNC_REGS:
	case KVM_CAP_ONE_REG:
	case KVM_CAP_ENABLE_CAP:
	case KVM_CAP_S390_CSS_SUPPORT:
	case KVM_CAP_IOEVENTFD:
	case KVM_CAP_DEVICE_CTRL:
	case KVM_CAP_S390_IRQCHIP:
	case KVM_CAP_VM_ATTRIBUTES:
	case KVM_CAP_MP_STATE:
	case KVM_CAP_IMMEDIATE_EXIT:
	case KVM_CAP_S390_INJECT_IRQ:
	case KVM_CAP_S390_USER_SIGP:
	case KVM_CAP_S390_USER_STSI:
	case KVM_CAP_S390_SKEYS:
	case KVM_CAP_S390_IRQ_STATE:
	case KVM_CAP_S390_USER_INSTR0:
	case KVM_CAP_S390_CMMA_MIGRATION:
	case KVM_CAP_S390_AIS:
	case KVM_CAP_S390_AIS_MIGRATION:
		r = 1;
		break;
	case KVM_CAP_S390_HPAGE_1M:
		r = 0;
		if (hpage && !kvm_is_ucontrol(kvm))
			r = 1;
		break;
	case KVM_CAP_S390_MEM_OP:
		r = MEM_OP_MAX_SIZE;
		break;
	case KVM_CAP_NR_VCPUS:
	case KVM_CAP_MAX_VCPUS:
	case KVM_CAP_MAX_VCPU_ID:
		r = KVM_S390_BSCA_CPU_SLOTS;
		if (!kvm_s390_use_sca_entries())
			r = KVM_MAX_VCPUS;
		else if (sclp.has_esca && sclp.has_64bscao)
			r = KVM_S390_ESCA_CPU_SLOTS;
		break;
	case KVM_CAP_S390_COW:
		r = MACHINE_HAS_ESOP;
		break;
	case KVM_CAP_S390_VECTOR_REGISTERS:
		r = MACHINE_HAS_VX;
		break;
	case KVM_CAP_S390_RI:
		r = test_facility(64);
		break;
	case KVM_CAP_S390_GS:
		r = test_facility(133);
		break;
	case KVM_CAP_S390_BPB:
		r = test_facility(82);
		break;
	default:
		r = 0;
	}
	return r;
}