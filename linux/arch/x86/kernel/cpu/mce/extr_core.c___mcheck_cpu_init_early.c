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
struct cpuinfo_x86 {scalar_t__ x86_vendor; } ;
struct TYPE_4__ {int overflow_recov; int succor; int smca; } ;
struct TYPE_3__ {int /*<<< orphan*/  misc; int /*<<< orphan*/  addr; int /*<<< orphan*/  status; int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_OVERFLOW_RECOV ; 
 int /*<<< orphan*/  X86_FEATURE_SMCA ; 
 int /*<<< orphan*/  X86_FEATURE_SUCCOR ; 
 scalar_t__ X86_VENDOR_AMD ; 
 scalar_t__ X86_VENDOR_HYGON ; 
 int /*<<< orphan*/  cpu_has (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 TYPE_2__ mce_flags ; 
 TYPE_1__ msr_ops ; 
 int /*<<< orphan*/  smca_addr_reg ; 
 int /*<<< orphan*/  smca_ctl_reg ; 
 int /*<<< orphan*/  smca_misc_reg ; 
 int /*<<< orphan*/  smca_status_reg ; 

__attribute__((used)) static void __mcheck_cpu_init_early(struct cpuinfo_x86 *c)
{
	if (c->x86_vendor == X86_VENDOR_AMD || c->x86_vendor == X86_VENDOR_HYGON) {
		mce_flags.overflow_recov = !!cpu_has(c, X86_FEATURE_OVERFLOW_RECOV);
		mce_flags.succor	 = !!cpu_has(c, X86_FEATURE_SUCCOR);
		mce_flags.smca		 = !!cpu_has(c, X86_FEATURE_SMCA);

		if (mce_flags.smca) {
			msr_ops.ctl	= smca_ctl_reg;
			msr_ops.status	= smca_status_reg;
			msr_ops.addr	= smca_addr_reg;
			msr_ops.misc	= smca_misc_reg;
		}
	}
}