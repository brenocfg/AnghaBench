#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_entry_ptr ;
struct TYPE_4__ {int apic_id; int /*<<< orphan*/  feature_flags; int /*<<< orphan*/  cpu_signature; int /*<<< orphan*/  cpu_flags; int /*<<< orphan*/  apic_version; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAPIC_VERSION ; 
 int /*<<< orphan*/  MPCT_ENTRY_PROCESSOR ; 
 int /*<<< orphan*/  MPEP_FEATURES ; 
 int /*<<< orphan*/  MPEP_SIG ; 
 int /*<<< orphan*/  PROCENTRY_FLAG_BP ; 
 int /*<<< orphan*/  PROCENTRY_FLAG_EN ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mpt_build_proc_entries(proc_entry_ptr mpep, int ncpu)
{
	int i;

	for (i = 0; i < ncpu; i++) {
		memset(mpep, 0, sizeof(*mpep));
		mpep->type = MPCT_ENTRY_PROCESSOR;
		mpep->apic_id = i; // XXX
		mpep->apic_version = LAPIC_VERSION;
		mpep->cpu_flags = PROCENTRY_FLAG_EN;
		if (i == 0)
			mpep->cpu_flags |= PROCENTRY_FLAG_BP;
		mpep->cpu_signature = MPEP_SIG;
		mpep->feature_flags = MPEP_FEATURES;
		mpep++;
	}
}