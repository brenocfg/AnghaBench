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
struct cpu_hw_sf {int /*<<< orphan*/  flags; int /*<<< orphan*/  qsi; } ;

/* Variables and functions */
 int PMC_FAILURE ; 
#define  PMC_INIT 129 
#define  PMC_RELEASE 128 
 int /*<<< orphan*/  PMU_F_RESERVED ; 
 int /*<<< orphan*/  cpu_hw_sf ; 
 int /*<<< orphan*/  deallocate_buffers (struct cpu_hw_sf*) ; 
 int /*<<< orphan*/  debug_sprintf_event (int /*<<< orphan*/ ,int,char*,struct cpu_hw_sf*) ; 
 int /*<<< orphan*/  memset (struct cpu_hw_sf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int qsi (int /*<<< orphan*/ *) ; 
 int sf_disable () ; 
 int /*<<< orphan*/  sfdbg ; 
 struct cpu_hw_sf* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void setup_pmc_cpu(void *flags)
{
	int err;
	struct cpu_hw_sf *cpusf = this_cpu_ptr(&cpu_hw_sf);

	err = 0;
	switch (*((int *) flags)) {
	case PMC_INIT:
		memset(cpusf, 0, sizeof(*cpusf));
		err = qsi(&cpusf->qsi);
		if (err)
			break;
		cpusf->flags |= PMU_F_RESERVED;
		err = sf_disable();
		if (err)
			pr_err("Switching off the sampling facility failed "
			       "with rc=%i\n", err);
		debug_sprintf_event(sfdbg, 5,
				    "setup_pmc_cpu: initialized: cpuhw=%p\n", cpusf);
		break;
	case PMC_RELEASE:
		cpusf->flags &= ~PMU_F_RESERVED;
		err = sf_disable();
		if (err) {
			pr_err("Switching off the sampling facility failed "
			       "with rc=%i\n", err);
		} else
			deallocate_buffers(cpusf);
		debug_sprintf_event(sfdbg, 5,
				    "setup_pmc_cpu: released: cpuhw=%p\n", cpusf);
		break;
	}
	if (err)
		*((int *) flags) |= PMC_FAILURE;
}