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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_2__ {scalar_t__ config_type; } ;

/* Variables and functions */
 int max_apic_id ; 
 int mp_maxid ; 
 int mp_ncpus ; 
 TYPE_1__* mpfps ; 
 int /*<<< orphan*/  mptable_probe_cpus_handler ; 
 int /*<<< orphan*/  mptable_walk_table (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mptable_probe_cpus(void)
{
	u_int cpu_mask;

	/* Is this a pre-defined config? */
	if (mpfps->config_type != 0) {
#ifdef SMP
		mp_ncpus = 2;
		mp_maxid = 1;
#endif
		max_apic_id = 1;
	} else {
		mptable_walk_table(mptable_probe_cpus_handler, &cpu_mask);
	}
	return (0);
}