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
struct mce_bank {scalar_t__ init; scalar_t__ ctl; } ;
struct mca_config {scalar_t__ bootlog; scalar_t__ monarch_timeout; int panic_timeout; } ;
struct cpuinfo_x86 {scalar_t__ x86_vendor; int x86; int x86_model; } ;
struct TYPE_2__ {int overflow_recov; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ USEC_PER_SEC ; 
 scalar_t__ X86_VENDOR_AMD ; 
 scalar_t__ X86_VENDOR_INTEL ; 
 scalar_t__ X86_VENDOR_UNKNOWN ; 
 int /*<<< orphan*/  clear_bit (int,unsigned long*) ; 
 struct mca_config mca_cfg ; 
 int /*<<< orphan*/  mce_banks_array ; 
 TYPE_1__ mce_flags ; 
 int /*<<< orphan*/  mce_num_banks ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  quirk_no_way_out ; 
 int /*<<< orphan*/  quirk_sandybridge_ifu ; 
 struct mce_bank* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int this_cpu_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __mcheck_cpu_apply_quirks(struct cpuinfo_x86 *c)
{
	struct mce_bank *mce_banks = this_cpu_ptr(mce_banks_array);
	struct mca_config *cfg = &mca_cfg;

	if (c->x86_vendor == X86_VENDOR_UNKNOWN) {
		pr_info("unknown CPU type - not enabling MCE support\n");
		return -EOPNOTSUPP;
	}

	/* This should be disabled by the BIOS, but isn't always */
	if (c->x86_vendor == X86_VENDOR_AMD) {
		if (c->x86 == 15 && this_cpu_read(mce_num_banks) > 4) {
			/*
			 * disable GART TBL walk error reporting, which
			 * trips off incorrectly with the IOMMU & 3ware
			 * & Cerberus:
			 */
			clear_bit(10, (unsigned long *)&mce_banks[4].ctl);
		}
		if (c->x86 < 0x11 && cfg->bootlog < 0) {
			/*
			 * Lots of broken BIOS around that don't clear them
			 * by default and leave crap in there. Don't log:
			 */
			cfg->bootlog = 0;
		}
		/*
		 * Various K7s with broken bank 0 around. Always disable
		 * by default.
		 */
		if (c->x86 == 6 && this_cpu_read(mce_num_banks) > 0)
			mce_banks[0].ctl = 0;

		/*
		 * overflow_recov is supported for F15h Models 00h-0fh
		 * even though we don't have a CPUID bit for it.
		 */
		if (c->x86 == 0x15 && c->x86_model <= 0xf)
			mce_flags.overflow_recov = 1;

	}

	if (c->x86_vendor == X86_VENDOR_INTEL) {
		/*
		 * SDM documents that on family 6 bank 0 should not be written
		 * because it aliases to another special BIOS controlled
		 * register.
		 * But it's not aliased anymore on model 0x1a+
		 * Don't ignore bank 0 completely because there could be a
		 * valid event later, merely don't write CTL0.
		 */

		if (c->x86 == 6 && c->x86_model < 0x1A && this_cpu_read(mce_num_banks) > 0)
			mce_banks[0].init = 0;

		/*
		 * All newer Intel systems support MCE broadcasting. Enable
		 * synchronization with a one second timeout.
		 */
		if ((c->x86 > 6 || (c->x86 == 6 && c->x86_model >= 0xe)) &&
			cfg->monarch_timeout < 0)
			cfg->monarch_timeout = USEC_PER_SEC;

		/*
		 * There are also broken BIOSes on some Pentium M and
		 * earlier systems:
		 */
		if (c->x86 == 6 && c->x86_model <= 13 && cfg->bootlog < 0)
			cfg->bootlog = 0;

		if (c->x86 == 6 && c->x86_model == 45)
			quirk_no_way_out = quirk_sandybridge_ifu;
	}
	if (cfg->monarch_timeout < 0)
		cfg->monarch_timeout = 0;
	if (cfg->bootlog != 0)
		cfg->panic_timeout = 30;

	return 0;
}