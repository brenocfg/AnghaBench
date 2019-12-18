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
typedef  int u32 ;
struct smca_hwid {unsigned int hwid_mcatype; int /*<<< orphan*/  count; } ;
struct TYPE_2__ {int id; scalar_t__ sysfs_id; struct smca_hwid* hwid; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct smca_hwid*) ; 
 int BIT (int) ; 
 unsigned int HWID_MCATYPE (int,int) ; 
 int MCI_IPID_HWID ; 
 int MCI_IPID_MCATYPE ; 
 int MSR_AMD64_SMCA_MCx_CONFIG (unsigned int) ; 
 int /*<<< orphan*/  MSR_AMD64_SMCA_MCx_IPID (unsigned int) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned int) ; 
 int /*<<< orphan*/  rdmsr_safe (int,int*,int*) ; 
 scalar_t__ rdmsr_safe_on_cpu (unsigned int,int /*<<< orphan*/ ,int*,int*) ; 
 TYPE_1__* smca_banks ; 
 struct smca_hwid* smca_hwid_mcatypes ; 
 int /*<<< orphan*/  smca_set_misc_banks_map (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  wrmsr (int,int,int) ; 

__attribute__((used)) static void smca_configure(unsigned int bank, unsigned int cpu)
{
	unsigned int i, hwid_mcatype;
	struct smca_hwid *s_hwid;
	u32 high, low;
	u32 smca_config = MSR_AMD64_SMCA_MCx_CONFIG(bank);

	/* Set appropriate bits in MCA_CONFIG */
	if (!rdmsr_safe(smca_config, &low, &high)) {
		/*
		 * OS is required to set the MCAX bit to acknowledge that it is
		 * now using the new MSR ranges and new registers under each
		 * bank. It also means that the OS will configure deferred
		 * errors in the new MCx_CONFIG register. If the bit is not set,
		 * uncorrectable errors will cause a system panic.
		 *
		 * MCA_CONFIG[MCAX] is bit 32 (0 in the high portion of the MSR.)
		 */
		high |= BIT(0);

		/*
		 * SMCA sets the Deferred Error Interrupt type per bank.
		 *
		 * MCA_CONFIG[DeferredIntTypeSupported] is bit 5, and tells us
		 * if the DeferredIntType bit field is available.
		 *
		 * MCA_CONFIG[DeferredIntType] is bits [38:37] ([6:5] in the
		 * high portion of the MSR). OS should set this to 0x1 to enable
		 * APIC based interrupt. First, check that no interrupt has been
		 * set.
		 */
		if ((low & BIT(5)) && !((high >> 5) & 0x3))
			high |= BIT(5);

		wrmsr(smca_config, low, high);
	}

	smca_set_misc_banks_map(bank, cpu);

	/* Return early if this bank was already initialized. */
	if (smca_banks[bank].hwid)
		return;

	if (rdmsr_safe_on_cpu(cpu, MSR_AMD64_SMCA_MCx_IPID(bank), &low, &high)) {
		pr_warn("Failed to read MCA_IPID for bank %d\n", bank);
		return;
	}

	hwid_mcatype = HWID_MCATYPE(high & MCI_IPID_HWID,
				    (high & MCI_IPID_MCATYPE) >> 16);

	for (i = 0; i < ARRAY_SIZE(smca_hwid_mcatypes); i++) {
		s_hwid = &smca_hwid_mcatypes[i];
		if (hwid_mcatype == s_hwid->hwid_mcatype) {
			smca_banks[bank].hwid = s_hwid;
			smca_banks[bank].id = low;
			smca_banks[bank].sysfs_id = s_hwid->count++;
			break;
		}
	}
}