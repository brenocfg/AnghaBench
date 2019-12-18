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
struct mce {int status; int /*<<< orphan*/  bank; } ;
typedef  enum context { ____Placeholder_context } context ;
struct TYPE_2__ {int /*<<< orphan*/  succor; } ;

/* Variables and functions */
 int IN_KERNEL ; 
 int MCE_AR_SEVERITY ; 
 int MCE_PANIC_SEVERITY ; 
 int MCI_CONFIG_MCAX ; 
 int MCI_STATUS_TCC ; 
 int MSR_AMD64_SMCA_MCx_CONFIG (int /*<<< orphan*/ ) ; 
 TYPE_1__ mce_flags ; 
 scalar_t__ rdmsr_safe (int,int*,int*) ; 

__attribute__((used)) static int mce_severity_amd_smca(struct mce *m, enum context err_ctx)
{
	u32 addr = MSR_AMD64_SMCA_MCx_CONFIG(m->bank);
	u32 low, high;

	/*
	 * We need to look at the following bits:
	 * - "succor" bit (data poisoning support), and
	 * - TCC bit (Task Context Corrupt)
	 * in MCi_STATUS to determine error severity.
	 */
	if (!mce_flags.succor)
		return MCE_PANIC_SEVERITY;

	if (rdmsr_safe(addr, &low, &high))
		return MCE_PANIC_SEVERITY;

	/* TCC (Task context corrupt). If set and if IN_KERNEL, panic. */
	if ((low & MCI_CONFIG_MCAX) &&
	    (m->status & MCI_STATUS_TCC) &&
	    (err_ctx == IN_KERNEL))
		return MCE_PANIC_SEVERITY;

	 /* ...otherwise invoke hwpoison handler. */
	return MCE_AR_SEVERITY;
}