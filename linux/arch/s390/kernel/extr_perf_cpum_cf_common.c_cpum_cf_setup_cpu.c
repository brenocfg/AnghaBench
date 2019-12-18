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
struct cpu_cf_events {int /*<<< orphan*/  flags; int /*<<< orphan*/  info; } ;

/* Variables and functions */
#define  PMC_INIT 129 
#define  PMC_RELEASE 128 
 int /*<<< orphan*/  PMU_F_RESERVED ; 
 int /*<<< orphan*/  cpu_cf_events ; 
 int /*<<< orphan*/  lcctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qctri (int /*<<< orphan*/ *) ; 
 struct cpu_cf_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpum_cf_setup_cpu(void *flags)
{
	struct cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);

	switch (*((int *) flags)) {
	case PMC_INIT:
		memset(&cpuhw->info, 0, sizeof(cpuhw->info));
		qctri(&cpuhw->info);
		cpuhw->flags |= PMU_F_RESERVED;
		break;

	case PMC_RELEASE:
		cpuhw->flags &= ~PMU_F_RESERVED;
		break;
	}

	/* Disable CPU counter sets */
	lcctl(0);
}