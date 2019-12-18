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
struct cpuinfo_x86 {int dummy; } ;
struct TYPE_2__ {int disabled; } ;

/* Variables and functions */
 scalar_t__ __mcheck_cpu_ancient_init (struct cpuinfo_x86*) ; 
 scalar_t__ __mcheck_cpu_apply_quirks (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  __mcheck_cpu_cap_init () ; 
 int /*<<< orphan*/  __mcheck_cpu_check_banks () ; 
 int /*<<< orphan*/  __mcheck_cpu_init_clear_banks () ; 
 int /*<<< orphan*/  __mcheck_cpu_init_early (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  __mcheck_cpu_init_generic () ; 
 int /*<<< orphan*/  __mcheck_cpu_init_vendor (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  __mcheck_cpu_setup_timer () ; 
 int /*<<< orphan*/  do_machine_check ; 
 int /*<<< orphan*/  machine_check_vector ; 
 TYPE_1__ mca_cfg ; 
 int /*<<< orphan*/  mce_available (struct cpuinfo_x86*) ; 
 scalar_t__ mce_gen_pool_init () ; 
 int /*<<< orphan*/  pr_emerg (char*) ; 

void mcheck_cpu_init(struct cpuinfo_x86 *c)
{
	if (mca_cfg.disabled)
		return;

	if (__mcheck_cpu_ancient_init(c))
		return;

	if (!mce_available(c))
		return;

	__mcheck_cpu_cap_init();

	if (__mcheck_cpu_apply_quirks(c) < 0) {
		mca_cfg.disabled = 1;
		return;
	}

	if (mce_gen_pool_init()) {
		mca_cfg.disabled = 1;
		pr_emerg("Couldn't allocate MCE records pool!\n");
		return;
	}

	machine_check_vector = do_machine_check;

	__mcheck_cpu_init_early(c);
	__mcheck_cpu_init_generic();
	__mcheck_cpu_init_vendor(c);
	__mcheck_cpu_init_clear_banks();
	__mcheck_cpu_check_banks();
	__mcheck_cpu_setup_timer();
}