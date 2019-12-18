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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct xsave_limits {unsigned int xcr0_allowed; unsigned int xsave_max_size; int /*<<< orphan*/  xsave_enabled; } ;
struct vm {int dummy; } ;
typedef  enum x2apic_state { ____Placeholder_x2apic_state } x2apic_state ;

/* Variables and functions */
 unsigned int AMDFEID_CLZERO ; 
 unsigned int AMDFEID_IRPERF ; 
 unsigned int AMDFEID_XSAVEERPTR ; 
 unsigned int AMDID2_IBS ; 
 unsigned int AMDID2_MWAITX ; 
 unsigned int AMDID2_NODE_ID ; 
 unsigned int AMDID2_OSVW ; 
 unsigned int AMDID2_PCXC ; 
 unsigned int AMDID2_PNXC ; 
 unsigned int AMDID2_PTSCEL2I ; 
 unsigned int AMDID2_SVM ; 
 int AMDID_COREID_SIZE_SHIFT ; 
 unsigned int AMDID_RDTSCP ; 
 unsigned int AMDPM_TSC_INVARIANT ; 
 int /*<<< orphan*/  CACHE_LINE_SIZE ; 
 unsigned int CPUID2_EST ; 
 unsigned int CPUID2_HV ; 
 unsigned int CPUID2_MON ; 
 unsigned int CPUID2_OSXSAVE ; 
 unsigned int CPUID2_PDCM ; 
 unsigned int CPUID2_SMX ; 
 unsigned int CPUID2_TM2 ; 
 unsigned int CPUID2_TSCDLT ; 
 unsigned int CPUID2_VMX ; 
 unsigned int CPUID2_X2APIC ; 
 unsigned int CPUID2_XSAVE ; 
#define  CPUID_0000_0000 147 
#define  CPUID_0000_0001 146 
 int CPUID_0000_0001_APICID_SHIFT ; 
#define  CPUID_0000_0002 145 
#define  CPUID_0000_0003 144 
#define  CPUID_0000_0004 143 
#define  CPUID_0000_0006 142 
#define  CPUID_0000_0007 141 
#define  CPUID_0000_000A 140 
#define  CPUID_0000_000B 139 
#define  CPUID_0000_000D 138 
#define  CPUID_8000_0000 137 
#define  CPUID_8000_0001 136 
#define  CPUID_8000_0002 135 
#define  CPUID_8000_0003 134 
#define  CPUID_8000_0004 133 
#define  CPUID_8000_0006 132 
#define  CPUID_8000_0007 131 
#define  CPUID_8000_0008 130 
#define  CPUID_8000_001D 129 
#define  CPUID_8000_001E 128 
 unsigned int CPUID_ACPI ; 
 unsigned int CPUID_DS ; 
 unsigned int CPUID_EXTSTATE_XSAVEOPT ; 
 unsigned int CPUID_HTT ; 
 unsigned int CPUID_HTT_CORES ; 
 unsigned int CPUID_LOCAL_APIC_ID ; 
 unsigned int CPUID_MCA ; 
 unsigned int CPUID_MCE ; 
 unsigned int CPUID_MTRR ; 
 unsigned int CPUID_STDEXT3_MD_CLEAR ; 
 unsigned int CPUID_STDEXT_AVX2 ; 
 unsigned int CPUID_STDEXT_AVX512CD ; 
 unsigned int CPUID_STDEXT_AVX512ER ; 
 unsigned int CPUID_STDEXT_AVX512F ; 
 unsigned int CPUID_STDEXT_AVX512PF ; 
 unsigned int CPUID_STDEXT_BMI1 ; 
 unsigned int CPUID_STDEXT_BMI2 ; 
 unsigned int CPUID_STDEXT_ERMS ; 
 unsigned int CPUID_STDEXT_FSGSBASE ; 
 unsigned int CPUID_STDEXT_HLE ; 
 unsigned int CPUID_STDEXT_INVPCID ; 
 unsigned int CPUID_STDEXT_RDSEED ; 
 unsigned int CPUID_STDEXT_RTM ; 
 unsigned int CPUID_STDEXT_SHA ; 
 unsigned int CPUID_TM ; 
 int CPUID_TO_FAMILY (int /*<<< orphan*/ ) ; 
 int CPUID_TYPE_CORE ; 
 int CPUID_TYPE_SMT ; 
 int CPUID_VM_HIGH ; 
 unsigned int CPUTPM1_ARAT ; 
 int CR4_XSAVE ; 
 void* MIN (int,unsigned int) ; 
 int /*<<< orphan*/  VCPU_CTR2 (struct vm*,int,char*,int,int) ; 
 int /*<<< orphan*/  VM_CAP_ENABLE_INVPCID ; 
 int /*<<< orphan*/  VM_REG_GUEST_CR4 ; 
 int X2APIC_DISABLED ; 
 int /*<<< orphan*/  atomic_add_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,unsigned int*,int) ; 
 int /*<<< orphan*/  bhyve_id ; 
 int /*<<< orphan*/  bhyve_xcpuids ; 
 int cpu_exthigh ; 
 int cpu_high ; 
 int /*<<< orphan*/  cpu_id ; 
 int /*<<< orphan*/  cpuid_count (int,int,unsigned int*) ; 
 int /*<<< orphan*/  cpuid_leaf_b ; 
 int /*<<< orphan*/  do_cpuid (int,unsigned int*) ; 
 int log2 (unsigned int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  smp_tsc ; 
 int /*<<< orphan*/  tsc_is_invariant ; 
 int vm_get_capability (struct vm*,int,int /*<<< orphan*/ ,int*) ; 
 int vm_get_register (struct vm*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  vm_get_topology (struct vm*,int*,int*,int*,int*) ; 
 int vm_get_x2apic_state (struct vm*,int,int*) ; 
 struct xsave_limits* vmm_get_xsave_limits () ; 
 int /*<<< orphan*/  vmm_is_amd () ; 
 int /*<<< orphan*/  vmm_is_intel () ; 

int
x86_emulate_cpuid(struct vm *vm, int vcpu_id,
		  uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx)
{
	const struct xsave_limits *limits;
	uint64_t cr4;
	int error, enable_invpcid, level, width, x2apic_id;
	unsigned int func, regs[4], logical_cpus;
	enum x2apic_state x2apic_state;
	uint16_t cores, maxcpus, sockets, threads;

	VCPU_CTR2(vm, vcpu_id, "cpuid %#x,%#x", *eax, *ecx);

	/*
	 * Requests for invalid CPUID levels should map to the highest
	 * available level instead.
	 */
	if (cpu_exthigh != 0 && *eax >= 0x80000000) {
		if (*eax > cpu_exthigh)
			*eax = cpu_exthigh;
	} else if (*eax >= 0x40000000) {
		if (*eax > CPUID_VM_HIGH)
			*eax = CPUID_VM_HIGH;
	} else if (*eax > cpu_high) {
		*eax = cpu_high;
	}

	func = *eax;

	/*
	 * In general the approach used for CPU topology is to
	 * advertise a flat topology where all CPUs are packages with
	 * no multi-core or SMT.
	 */
	switch (func) {
		/*
		 * Pass these through to the guest
		 */
		case CPUID_0000_0000:
		case CPUID_0000_0002:
		case CPUID_0000_0003:
		case CPUID_8000_0000:
		case CPUID_8000_0002:
		case CPUID_8000_0003:
		case CPUID_8000_0004:
		case CPUID_8000_0006:
			cpuid_count(*eax, *ecx, regs);
			break;
		case CPUID_8000_0008:
			cpuid_count(*eax, *ecx, regs);
			if (vmm_is_amd()) {
				/*
				 * As on Intel (0000_0007:0, EDX), mask out
				 * unsupported or unsafe AMD extended features
				 * (8000_0008 EBX).
				 */
				regs[1] &= (AMDFEID_CLZERO | AMDFEID_IRPERF |
				    AMDFEID_XSAVEERPTR);

				vm_get_topology(vm, &sockets, &cores, &threads,
				    &maxcpus);
				/*
				 * Here, width is ApicIdCoreIdSize, present on
				 * at least Family 15h and newer.  It
				 * represents the "number of bits in the
				 * initial apicid that indicate thread id
				 * within a package."
				 *
				 * Our topo_probe_amd() uses it for
				 * pkg_id_shift and other OSes may rely on it.
				 */
				width = MIN(0xF, log2(threads * cores));
				if (width < 0x4)
					width = 0;
				logical_cpus = MIN(0xFF, threads * cores - 1);
				regs[2] = (width << AMDID_COREID_SIZE_SHIFT) | logical_cpus;
			}
			break;

		case CPUID_8000_0001:
			cpuid_count(*eax, *ecx, regs);

			/*
			 * Hide SVM from guest.
			 */
			regs[2] &= ~AMDID2_SVM;

			/*
			 * Don't advertise extended performance counter MSRs
			 * to the guest.
			 */
			regs[2] &= ~AMDID2_PCXC;
			regs[2] &= ~AMDID2_PNXC;
			regs[2] &= ~AMDID2_PTSCEL2I;

			/*
			 * Don't advertise Instruction Based Sampling feature.
			 */
			regs[2] &= ~AMDID2_IBS;

			/* NodeID MSR not available */
			regs[2] &= ~AMDID2_NODE_ID;

			/* Don't advertise the OS visible workaround feature */
			regs[2] &= ~AMDID2_OSVW;

			/* Hide mwaitx/monitorx capability from the guest */
			regs[2] &= ~AMDID2_MWAITX;

			/*
			 * Hide rdtscp/ia32_tsc_aux until we know how
			 * to deal with them.
			 */
			regs[3] &= ~AMDID_RDTSCP;
			break;

		case CPUID_8000_0007:
			/*
			 * AMD uses this leaf to advertise the processor's
			 * power monitoring and RAS capabilities. These
			 * features are hardware-specific and exposing
			 * them to a guest doesn't make a lot of sense.
			 *
			 * Intel uses this leaf only to advertise the
			 * "Invariant TSC" feature with all other bits
			 * being reserved (set to zero).
			 */
			regs[0] = 0;
			regs[1] = 0;
			regs[2] = 0;
			regs[3] = 0;

			/*
			 * "Invariant TSC" can be advertised to the guest if:
			 * - host TSC frequency is invariant
			 * - host TSCs are synchronized across physical cpus
			 *
			 * XXX This still falls short because the vcpu
			 * can observe the TSC moving backwards as it
			 * migrates across physical cpus. But at least
			 * it should discourage the guest from using the
			 * TSC to keep track of time.
			 */
			if (tsc_is_invariant && smp_tsc)
				regs[3] |= AMDPM_TSC_INVARIANT;
			break;

		case CPUID_8000_001D:
			/* AMD Cache topology, like 0000_0004 for Intel. */
			if (!vmm_is_amd())
				goto default_leaf;

			/*
			 * Similar to Intel, generate a ficticious cache
			 * topology for the guest with L3 shared by the
			 * package, and L1 and L2 local to a core.
			 */
			vm_get_topology(vm, &sockets, &cores, &threads,
			    &maxcpus);
			switch (*ecx) {
			case 0:
				logical_cpus = threads;
				level = 1;
				func = 1;	/* data cache */
				break;
			case 1:
				logical_cpus = threads;
				level = 2;
				func = 3;	/* unified cache */
				break;
			case 2:
				logical_cpus = threads * cores;
				level = 3;
				func = 3;	/* unified cache */
				break;
			default:
				logical_cpus = 0;
				level = 0;
				func = 0;
				break;
			}

			logical_cpus = MIN(0xfff, logical_cpus - 1);
			regs[0] = (logical_cpus << 14) | (1 << 8) |
			    (level << 5) | func;
			regs[1] = (func > 0) ? (CACHE_LINE_SIZE - 1) : 0;
			regs[2] = 0;
			regs[3] = 0;
			break;

		case CPUID_8000_001E:
			/* AMD Family 16h+ additional identifiers */
			if (!vmm_is_amd() || CPUID_TO_FAMILY(cpu_id) < 0x16)
				goto default_leaf;

			vm_get_topology(vm, &sockets, &cores, &threads,
			    &maxcpus);
			regs[0] = vcpu_id;
			threads = MIN(0xFF, threads - 1);
			regs[1] = (threads << 8) |
			    (vcpu_id >> log2(threads + 1));
			/*
			 * XXX Bhyve topology cannot yet represent >1 node per
			 * processor.
			 */
			regs[2] = 0;
			regs[3] = 0;
			break;

		case CPUID_0000_0001:
			do_cpuid(1, regs);

			error = vm_get_x2apic_state(vm, vcpu_id, &x2apic_state);
			if (error) {
				panic("x86_emulate_cpuid: error %d "
				      "fetching x2apic state", error);
			}

			/*
			 * Override the APIC ID only in ebx
			 */
			regs[1] &= ~(CPUID_LOCAL_APIC_ID);
			regs[1] |= (vcpu_id << CPUID_0000_0001_APICID_SHIFT);

			/*
			 * Don't expose VMX, SpeedStep, TME or SMX capability.
			 * Advertise x2APIC capability and Hypervisor guest.
			 */
			regs[2] &= ~(CPUID2_VMX | CPUID2_EST | CPUID2_TM2);
			regs[2] &= ~(CPUID2_SMX);

			regs[2] |= CPUID2_HV;

			if (x2apic_state != X2APIC_DISABLED)
				regs[2] |= CPUID2_X2APIC;
			else
				regs[2] &= ~CPUID2_X2APIC;

			/*
			 * Only advertise CPUID2_XSAVE in the guest if
			 * the host is using XSAVE.
			 */
			if (!(regs[2] & CPUID2_OSXSAVE))
				regs[2] &= ~CPUID2_XSAVE;

			/*
			 * If CPUID2_XSAVE is being advertised and the
			 * guest has set CR4_XSAVE, set
			 * CPUID2_OSXSAVE.
			 */
			regs[2] &= ~CPUID2_OSXSAVE;
			if (regs[2] & CPUID2_XSAVE) {
				error = vm_get_register(vm, vcpu_id,
				    VM_REG_GUEST_CR4, &cr4);
				if (error)
					panic("x86_emulate_cpuid: error %d "
					      "fetching %%cr4", error);
				if (cr4 & CR4_XSAVE)
					regs[2] |= CPUID2_OSXSAVE;
			}

			/*
			 * Hide monitor/mwait until we know how to deal with
			 * these instructions.
			 */
			regs[2] &= ~CPUID2_MON;

                        /*
			 * Hide the performance and debug features.
			 */
			regs[2] &= ~CPUID2_PDCM;

			/*
			 * No TSC deadline support in the APIC yet
			 */
			regs[2] &= ~CPUID2_TSCDLT;

			/*
			 * Hide thermal monitoring
			 */
			regs[3] &= ~(CPUID_ACPI | CPUID_TM);

			/*
			 * Hide the debug store capability.
			 */
			regs[3] &= ~CPUID_DS;

			/*
			 * Advertise the Machine Check and MTRR capability.
			 *
			 * Some guest OSes (e.g. Windows) will not boot if
			 * these features are absent.
			 */
			regs[3] |= (CPUID_MCA | CPUID_MCE | CPUID_MTRR);

			vm_get_topology(vm, &sockets, &cores, &threads,
			    &maxcpus);
			logical_cpus = threads * cores;
			regs[1] &= ~CPUID_HTT_CORES;
			regs[1] |= (logical_cpus & 0xff) << 16;
			regs[3] |= CPUID_HTT;
			break;

		case CPUID_0000_0004:
			cpuid_count(*eax, *ecx, regs);

			if (regs[0] || regs[1] || regs[2] || regs[3]) {
				vm_get_topology(vm, &sockets, &cores, &threads,
				    &maxcpus);
				regs[0] &= 0x3ff;
				regs[0] |= (cores - 1) << 26;
				/*
				 * Cache topology:
				 * - L1 and L2 are shared only by the logical
				 *   processors in a single core.
				 * - L3 and above are shared by all logical
				 *   processors in the package.
				 */
				logical_cpus = threads;
				level = (regs[0] >> 5) & 0x7;
				if (level >= 3)
					logical_cpus *= cores;
				regs[0] |= (logical_cpus - 1) << 14;
			}
			break;

		case CPUID_0000_0007:
			regs[0] = 0;
			regs[1] = 0;
			regs[2] = 0;
			regs[3] = 0;

			/* leaf 0 */
			if (*ecx == 0) {
				cpuid_count(*eax, *ecx, regs);

				/* Only leaf 0 is supported */
				regs[0] = 0;

				/*
				 * Expose known-safe features.
				 */
				regs[1] &= (CPUID_STDEXT_FSGSBASE |
				    CPUID_STDEXT_BMI1 | CPUID_STDEXT_HLE |
				    CPUID_STDEXT_AVX2 | CPUID_STDEXT_BMI2 |
				    CPUID_STDEXT_ERMS | CPUID_STDEXT_RTM |
				    CPUID_STDEXT_AVX512F |
				    CPUID_STDEXT_RDSEED |
				    CPUID_STDEXT_AVX512PF |
				    CPUID_STDEXT_AVX512ER |
				    CPUID_STDEXT_AVX512CD | CPUID_STDEXT_SHA);
				regs[2] = 0;
				regs[3] &= CPUID_STDEXT3_MD_CLEAR;

				/* Advertise INVPCID if it is enabled. */
				error = vm_get_capability(vm, vcpu_id,
				    VM_CAP_ENABLE_INVPCID, &enable_invpcid);
				if (error == 0 && enable_invpcid)
					regs[1] |= CPUID_STDEXT_INVPCID;
			}
			break;

		case CPUID_0000_0006:
			regs[0] = CPUTPM1_ARAT;
			regs[1] = 0;
			regs[2] = 0;
			regs[3] = 0;
			break;

		case CPUID_0000_000A:
			/*
			 * Handle the access, but report 0 for
			 * all options
			 */
			regs[0] = 0;
			regs[1] = 0;
			regs[2] = 0;
			regs[3] = 0;
			break;

		case CPUID_0000_000B:
			/*
			 * Intel processor topology enumeration
			 */
			if (vmm_is_intel()) {
				vm_get_topology(vm, &sockets, &cores, &threads,
				    &maxcpus);
				if (*ecx == 0) {
					logical_cpus = threads;
					width = log2(logical_cpus);
					level = CPUID_TYPE_SMT;
					x2apic_id = vcpu_id;
				}

				if (*ecx == 1) {
					logical_cpus = threads * cores;
					width = log2(logical_cpus);
					level = CPUID_TYPE_CORE;
					x2apic_id = vcpu_id;
				}

				if (!cpuid_leaf_b || *ecx >= 2) {
					width = 0;
					logical_cpus = 0;
					level = 0;
					x2apic_id = 0;
				}

				regs[0] = width & 0x1f;
				regs[1] = logical_cpus & 0xffff;
				regs[2] = (level << 8) | (*ecx & 0xff);
				regs[3] = x2apic_id;
			} else {
				regs[0] = 0;
				regs[1] = 0;
				regs[2] = 0;
				regs[3] = 0;
			}
			break;

		case CPUID_0000_000D:
			limits = vmm_get_xsave_limits();
			if (!limits->xsave_enabled) {
				regs[0] = 0;
				regs[1] = 0;
				regs[2] = 0;
				regs[3] = 0;
				break;
			}

			cpuid_count(*eax, *ecx, regs);
			switch (*ecx) {
			case 0:
				/*
				 * Only permit the guest to use bits
				 * that are active in the host in
				 * %xcr0.  Also, claim that the
				 * maximum save area size is
				 * equivalent to the host's current
				 * save area size.  Since this runs
				 * "inside" of vmrun(), it runs with
				 * the guest's xcr0, so the current
				 * save area size is correct as-is.
				 */
				regs[0] &= limits->xcr0_allowed;
				regs[2] = limits->xsave_max_size;
				regs[3] &= (limits->xcr0_allowed >> 32);
				break;
			case 1:
				/* Only permit XSAVEOPT. */
				regs[0] &= CPUID_EXTSTATE_XSAVEOPT;
				regs[1] = 0;
				regs[2] = 0;
				regs[3] = 0;
				break;
			default:
				/*
				 * If the leaf is for a permitted feature,
				 * pass through as-is, otherwise return
				 * all zeroes.
				 */
				if (!(limits->xcr0_allowed & (1ul << *ecx))) {
					regs[0] = 0;
					regs[1] = 0;
					regs[2] = 0;
					regs[3] = 0;
				}
				break;
			}
			break;

		case 0x40000000:
			regs[0] = CPUID_VM_HIGH;
			bcopy(bhyve_id, &regs[1], 4);
			bcopy(bhyve_id + 4, &regs[2], 4);
			bcopy(bhyve_id + 8, &regs[3], 4);
			break;

		default:
default_leaf:
			/*
			 * The leaf value has already been clamped so
			 * simply pass this through, keeping count of
			 * how many unhandled leaf values have been seen.
			 */
			atomic_add_long(&bhyve_xcpuids, 1);
			cpuid_count(*eax, *ecx, regs);
			break;
	}

	*eax = regs[0];
	*ebx = regs[1];
	*ecx = regs[2];
	*edx = regs[3];

	return (1);
}