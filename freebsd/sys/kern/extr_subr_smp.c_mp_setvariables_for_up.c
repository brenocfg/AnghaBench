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

/* Variables and functions */
 int /*<<< orphan*/  CPU_SETOF (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  all_cpus ; 
 int /*<<< orphan*/  cpuid ; 
 scalar_t__ mp_maxid ; 
 int mp_ncores ; 
 int mp_ncpus ; 

__attribute__((used)) static void
mp_setvariables_for_up(void *dummy)
{
	mp_ncpus = 1;
	mp_ncores = 1;
	mp_maxid = PCPU_GET(cpuid);
	CPU_SETOF(mp_maxid, &all_cpus);
	KASSERT(PCPU_GET(cpuid) == 0, ("UP must have a CPU ID of zero"));
}