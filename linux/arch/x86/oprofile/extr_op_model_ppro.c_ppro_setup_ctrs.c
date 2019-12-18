#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ version_id; scalar_t__ bit_width; } ;
union cpuid10_eax {TYPE_1__ split; int /*<<< orphan*/  full; } ;
typedef  int u64 ;
struct op_x86_model_spec {int reserved; } ;
struct op_msrs {TYPE_3__* controls; TYPE_2__* counters; } ;
struct TYPE_11__ {int /*<<< orphan*/  x86_model; int /*<<< orphan*/  x86; } ;
struct TYPE_10__ {int count; scalar_t__ enabled; } ;
struct TYPE_9__ {scalar_t__ addr; } ;
struct TYPE_8__ {scalar_t__ addr; } ;

/* Variables and functions */
 int ARCH_PERFMON_EVENTSEL_ENABLE ; 
 int /*<<< orphan*/  X86_FEATURE_ARCH_PERFMON ; 
 int __this_cpu_read (int /*<<< orphan*/ ) ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 TYPE_4__* counter_config ; 
 scalar_t__ counter_width ; 
 TYPE_5__ cpu_info ; 
 int /*<<< orphan*/  cpuid_eax (int) ; 
 int num_counters ; 
 int op_x86_get_ctrl (struct op_x86_model_spec const*,TYPE_4__*) ; 
 int /*<<< orphan*/  op_x86_warn_in_use (int) ; 
 int /*<<< orphan*/  rdmsrl (scalar_t__,int) ; 
 int* reset_value ; 
 int /*<<< orphan*/  wrmsrl (scalar_t__,int) ; 

__attribute__((used)) static void ppro_setup_ctrs(struct op_x86_model_spec const *model,
			    struct op_msrs const * const msrs)
{
	u64 val;
	int i;

	if (boot_cpu_has(X86_FEATURE_ARCH_PERFMON)) {
		union cpuid10_eax eax;
		eax.full = cpuid_eax(0xa);

		/*
		 * For Core2 (family 6, model 15), don't reset the
		 * counter width:
		 */
		if (!(eax.split.version_id == 0 &&
			__this_cpu_read(cpu_info.x86) == 6 &&
				__this_cpu_read(cpu_info.x86_model) == 15)) {

			if (counter_width < eax.split.bit_width)
				counter_width = eax.split.bit_width;
		}
	}

	/* clear all counters */
	for (i = 0; i < num_counters; ++i) {
		if (!msrs->controls[i].addr)
			continue;
		rdmsrl(msrs->controls[i].addr, val);
		if (val & ARCH_PERFMON_EVENTSEL_ENABLE)
			op_x86_warn_in_use(i);
		val &= model->reserved;
		wrmsrl(msrs->controls[i].addr, val);
		/*
		 * avoid a false detection of ctr overflows in NMI *
		 * handler
		 */
		wrmsrl(msrs->counters[i].addr, -1LL);
	}

	/* enable active counters */
	for (i = 0; i < num_counters; ++i) {
		if (counter_config[i].enabled && msrs->counters[i].addr) {
			reset_value[i] = counter_config[i].count;
			wrmsrl(msrs->counters[i].addr, -reset_value[i]);
			rdmsrl(msrs->controls[i].addr, val);
			val &= model->reserved;
			val |= op_x86_get_ctrl(model, &counter_config[i]);
			wrmsrl(msrs->controls[i].addr, val);
		} else {
			reset_value[i] = 0;
		}
	}
}