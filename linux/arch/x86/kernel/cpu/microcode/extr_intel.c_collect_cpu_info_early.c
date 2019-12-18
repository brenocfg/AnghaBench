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
struct cpu_signature {unsigned int sig; int pf; int /*<<< orphan*/  rev; int /*<<< orphan*/  member_0; } ;
struct ucode_cpu_info {int valid; struct cpu_signature cpu_sig; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_PLATFORM_ID ; 
 int /*<<< orphan*/  intel_get_microcode_revision () ; 
 int /*<<< orphan*/  memset (struct ucode_cpu_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  native_cpuid (unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  native_rdmsr (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 unsigned int x86_family (unsigned int) ; 
 unsigned int x86_model (unsigned int) ; 

__attribute__((used)) static int collect_cpu_info_early(struct ucode_cpu_info *uci)
{
	unsigned int val[2];
	unsigned int family, model;
	struct cpu_signature csig = { 0 };
	unsigned int eax, ebx, ecx, edx;

	memset(uci, 0, sizeof(*uci));

	eax = 0x00000001;
	ecx = 0;
	native_cpuid(&eax, &ebx, &ecx, &edx);
	csig.sig = eax;

	family = x86_family(eax);
	model  = x86_model(eax);

	if ((model >= 5) || (family > 6)) {
		/* get processor flags from MSR 0x17 */
		native_rdmsr(MSR_IA32_PLATFORM_ID, val[0], val[1]);
		csig.pf = 1 << ((val[1] >> 18) & 7);
	}

	csig.rev = intel_get_microcode_revision();

	uci->cpu_sig = csig;
	uci->valid = 1;

	return 0;
}