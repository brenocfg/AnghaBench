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
typedef  int u_int ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ kgdb_lookup (char*) ; 
 scalar_t__ stoppcbs ; 

CORE_ADDR
kgdb_trgt_stop_pcb(u_int cpuid, u_int pcbsz)
{
	static int once = 0;

	if (stoppcbs == 0 && !once) {
		once = 1;
		stoppcbs = kgdb_lookup("stoppcbs");
	}
	if (stoppcbs == 0)
		return 0;

	return (stoppcbs + pcbsz * cpuid);
}