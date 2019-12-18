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
struct TYPE_2__ {int (* has_emulated_msr ) (int /*<<< orphan*/ ) ;int (* get_nested_state ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * nested_enable_evmcs; int /*<<< orphan*/ * enable_direct_tlbflush; int /*<<< orphan*/  (* cpu_has_accelerated_tpr ) () ;} ;

/* Variables and functions */
#define  KVM_CAP_ADJUST_CLOCK 193 
#define  KVM_CAP_ASYNC_PF 192 
#define  KVM_CAP_CLOCKSOURCE 191 
#define  KVM_CAP_DEBUGREGS 190 
#define  KVM_CAP_DISABLE_QUIRKS 189 
#define  KVM_CAP_EXCEPTION_PAYLOAD 188 
#define  KVM_CAP_EXT_CPUID 187 
#define  KVM_CAP_EXT_EMUL_CPUID 186 
#define  KVM_CAP_GET_MSR_FEATURES 185 
#define  KVM_CAP_GET_TSC_KHZ 184 
#define  KVM_CAP_HLT 183 
#define  KVM_CAP_HYPERV 182 
#define  KVM_CAP_HYPERV_CPUID 181 
#define  KVM_CAP_HYPERV_DIRECT_TLBFLUSH 180 
#define  KVM_CAP_HYPERV_ENLIGHTENED_VMCS 179 
#define  KVM_CAP_HYPERV_EVENTFD 178 
#define  KVM_CAP_HYPERV_SEND_IPI 177 
#define  KVM_CAP_HYPERV_SPIN 176 
#define  KVM_CAP_HYPERV_SYNIC 175 
#define  KVM_CAP_HYPERV_SYNIC2 174 
#define  KVM_CAP_HYPERV_TIME 173 
#define  KVM_CAP_HYPERV_TLBFLUSH 172 
#define  KVM_CAP_HYPERV_VAPIC 171 
#define  KVM_CAP_HYPERV_VP_INDEX 170 
#define  KVM_CAP_IMMEDIATE_EXIT 169 
#define  KVM_CAP_IOAPIC_POLARITY_IGNORED 168 
#define  KVM_CAP_IOEVENTFD 167 
#define  KVM_CAP_IOEVENTFD_NO_LENGTH 166 
#define  KVM_CAP_IRQCHIP 165 
#define  KVM_CAP_IRQ_INJECT_STATUS 164 
#define  KVM_CAP_KVMCLOCK_CTRL 163 
#define  KVM_CAP_MAX_VCPUS 162 
#define  KVM_CAP_MAX_VCPU_ID 161 
#define  KVM_CAP_MCE 160 
#define  KVM_CAP_MMU_SHADOW_CACHE_CONTROL 159 
#define  KVM_CAP_MP_STATE 158 
#define  KVM_CAP_MSR_PLATFORM_INFO 157 
#define  KVM_CAP_NESTED_STATE 156 
#define  KVM_CAP_NOP_IO_DELAY 155 
#define  KVM_CAP_NR_VCPUS 154 
#define  KVM_CAP_PCI_SEGMENT 153 
#define  KVM_CAP_PIT 152 
#define  KVM_CAP_PIT2 151 
#define  KVM_CAP_PIT_STATE2 150 
#define  KVM_CAP_PMU_EVENT_FILTER 149 
#define  KVM_CAP_PV_MMU 148 
#define  KVM_CAP_READONLY_MEM 147 
#define  KVM_CAP_REINJECT_CONTROL 146 
#define  KVM_CAP_SET_BOOT_CPU_ID 145 
#define  KVM_CAP_SET_IDENTITY_MAP_ADDR 144 
#define  KVM_CAP_SET_TSS_ADDR 143 
#define  KVM_CAP_SPLIT_IRQCHIP 142 
#define  KVM_CAP_SYNC_MMU 141 
#define  KVM_CAP_SYNC_REGS 140 
#define  KVM_CAP_TSC_CONTROL 139 
#define  KVM_CAP_TSC_DEADLINE_TIMER 138 
#define  KVM_CAP_USER_NMI 137 
#define  KVM_CAP_VAPIC 136 
#define  KVM_CAP_VCPU_EVENTS 135 
#define  KVM_CAP_X2APIC_API 134 
#define  KVM_CAP_X86_DISABLE_EXITS 133 
#define  KVM_CAP_X86_ROBUST_SINGLESTEP 132 
#define  KVM_CAP_X86_SMM 131 
#define  KVM_CAP_XCRS 130 
#define  KVM_CAP_XEN_HVM 129 
#define  KVM_CAP_XSAVE 128 
 int KVM_CLOCK_TSC_STABLE ; 
 int KVM_MAX_MCE_BANKS ; 
 int KVM_MAX_VCPUS ; 
 int KVM_MAX_VCPU_ID ; 
 int KVM_SOFT_MAX_VCPUS ; 
 int KVM_SYNC_X86_VALID_FIELDS ; 
 int KVM_X2APIC_API_VALID_FLAGS ; 
 int KVM_X86_DISABLE_EXITS_CSTATE ; 
 int KVM_X86_DISABLE_EXITS_HLT ; 
 int KVM_X86_DISABLE_EXITS_MWAIT ; 
 int KVM_X86_DISABLE_EXITS_PAUSE ; 
 int /*<<< orphan*/  MSR_IA32_SMBASE ; 
 int /*<<< orphan*/  X86_FEATURE_XSAVE ; 
 int boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_can_mwait_in_guest () ; 
 int kvm_has_tsc_control ; 
 TYPE_1__* kvm_x86_ops ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 () ; 
 int stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int kvm_vm_ioctl_check_extension(struct kvm *kvm, long ext)
{
	int r = 0;

	switch (ext) {
	case KVM_CAP_IRQCHIP:
	case KVM_CAP_HLT:
	case KVM_CAP_MMU_SHADOW_CACHE_CONTROL:
	case KVM_CAP_SET_TSS_ADDR:
	case KVM_CAP_EXT_CPUID:
	case KVM_CAP_EXT_EMUL_CPUID:
	case KVM_CAP_CLOCKSOURCE:
	case KVM_CAP_PIT:
	case KVM_CAP_NOP_IO_DELAY:
	case KVM_CAP_MP_STATE:
	case KVM_CAP_SYNC_MMU:
	case KVM_CAP_USER_NMI:
	case KVM_CAP_REINJECT_CONTROL:
	case KVM_CAP_IRQ_INJECT_STATUS:
	case KVM_CAP_IOEVENTFD:
	case KVM_CAP_IOEVENTFD_NO_LENGTH:
	case KVM_CAP_PIT2:
	case KVM_CAP_PIT_STATE2:
	case KVM_CAP_SET_IDENTITY_MAP_ADDR:
	case KVM_CAP_XEN_HVM:
	case KVM_CAP_VCPU_EVENTS:
	case KVM_CAP_HYPERV:
	case KVM_CAP_HYPERV_VAPIC:
	case KVM_CAP_HYPERV_SPIN:
	case KVM_CAP_HYPERV_SYNIC:
	case KVM_CAP_HYPERV_SYNIC2:
	case KVM_CAP_HYPERV_VP_INDEX:
	case KVM_CAP_HYPERV_EVENTFD:
	case KVM_CAP_HYPERV_TLBFLUSH:
	case KVM_CAP_HYPERV_SEND_IPI:
	case KVM_CAP_HYPERV_CPUID:
	case KVM_CAP_PCI_SEGMENT:
	case KVM_CAP_DEBUGREGS:
	case KVM_CAP_X86_ROBUST_SINGLESTEP:
	case KVM_CAP_XSAVE:
	case KVM_CAP_ASYNC_PF:
	case KVM_CAP_GET_TSC_KHZ:
	case KVM_CAP_KVMCLOCK_CTRL:
	case KVM_CAP_READONLY_MEM:
	case KVM_CAP_HYPERV_TIME:
	case KVM_CAP_IOAPIC_POLARITY_IGNORED:
	case KVM_CAP_TSC_DEADLINE_TIMER:
	case KVM_CAP_DISABLE_QUIRKS:
	case KVM_CAP_SET_BOOT_CPU_ID:
 	case KVM_CAP_SPLIT_IRQCHIP:
	case KVM_CAP_IMMEDIATE_EXIT:
	case KVM_CAP_PMU_EVENT_FILTER:
	case KVM_CAP_GET_MSR_FEATURES:
	case KVM_CAP_MSR_PLATFORM_INFO:
	case KVM_CAP_EXCEPTION_PAYLOAD:
		r = 1;
		break;
	case KVM_CAP_SYNC_REGS:
		r = KVM_SYNC_X86_VALID_FIELDS;
		break;
	case KVM_CAP_ADJUST_CLOCK:
		r = KVM_CLOCK_TSC_STABLE;
		break;
	case KVM_CAP_X86_DISABLE_EXITS:
		r |=  KVM_X86_DISABLE_EXITS_HLT | KVM_X86_DISABLE_EXITS_PAUSE |
		      KVM_X86_DISABLE_EXITS_CSTATE;
		if(kvm_can_mwait_in_guest())
			r |= KVM_X86_DISABLE_EXITS_MWAIT;
		break;
	case KVM_CAP_X86_SMM:
		/* SMBASE is usually relocated above 1M on modern chipsets,
		 * and SMM handlers might indeed rely on 4G segment limits,
		 * so do not report SMM to be available if real mode is
		 * emulated via vm86 mode.  Still, do not go to great lengths
		 * to avoid userspace's usage of the feature, because it is a
		 * fringe case that is not enabled except via specific settings
		 * of the module parameters.
		 */
		r = kvm_x86_ops->has_emulated_msr(MSR_IA32_SMBASE);
		break;
	case KVM_CAP_VAPIC:
		r = !kvm_x86_ops->cpu_has_accelerated_tpr();
		break;
	case KVM_CAP_NR_VCPUS:
		r = KVM_SOFT_MAX_VCPUS;
		break;
	case KVM_CAP_MAX_VCPUS:
		r = KVM_MAX_VCPUS;
		break;
	case KVM_CAP_MAX_VCPU_ID:
		r = KVM_MAX_VCPU_ID;
		break;
	case KVM_CAP_PV_MMU:	/* obsolete */
		r = 0;
		break;
	case KVM_CAP_MCE:
		r = KVM_MAX_MCE_BANKS;
		break;
	case KVM_CAP_XCRS:
		r = boot_cpu_has(X86_FEATURE_XSAVE);
		break;
	case KVM_CAP_TSC_CONTROL:
		r = kvm_has_tsc_control;
		break;
	case KVM_CAP_X2APIC_API:
		r = KVM_X2APIC_API_VALID_FLAGS;
		break;
	case KVM_CAP_NESTED_STATE:
		r = kvm_x86_ops->get_nested_state ?
			kvm_x86_ops->get_nested_state(NULL, NULL, 0) : 0;
		break;
	case KVM_CAP_HYPERV_DIRECT_TLBFLUSH:
		r = kvm_x86_ops->enable_direct_tlbflush != NULL;
		break;
	case KVM_CAP_HYPERV_ENLIGHTENED_VMCS:
		r = kvm_x86_ops->nested_enable_evmcs != NULL;
		break;
	default:
		break;
	}
	return r;

}