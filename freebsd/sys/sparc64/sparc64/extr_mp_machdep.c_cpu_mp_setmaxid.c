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
 int /*<<< orphan*/  CPU_SETOF (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAXCPU ; 
 int MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_child (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_peer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  all_cpus ; 
 int /*<<< orphan*/  ap_count ; 
 int /*<<< orphan*/  curcpu ; 
 int /*<<< orphan*/  foreach_ap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mp_maxid ; 
 int mp_ncpus ; 

void
cpu_mp_setmaxid(void)
{

	CPU_SETOF(curcpu, &all_cpus);
	mp_ncpus = 1;

	foreach_ap(OF_child(OF_peer(0)), ap_count);
	mp_ncpus = MIN(mp_ncpus, MAXCPU);
	mp_maxid = mp_ncpus - 1;
}