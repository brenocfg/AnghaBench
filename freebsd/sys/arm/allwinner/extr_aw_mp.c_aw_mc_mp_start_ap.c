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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPUCFG_P_REG0 ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  aw_mc_mp_start_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcache_wbinv_poc_all () ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 
 int mp_ncpus ; 
 scalar_t__ mpentry ; 
 int /*<<< orphan*/  pmap_kextract (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aw_mc_mp_start_ap(bus_space_handle_t cpuscfg, bus_space_handle_t cpuxcfg,
    bus_space_handle_t prcm)
{
	int cluster, cpu;

	KASSERT(mp_ncpus <= 4, ("multiple clusters not yet supported"));

	dcache_wbinv_poc_all();

	bus_space_write_4(fdtbus_bs_tag, cpuscfg, CPUCFG_P_REG0,
	    pmap_kextract((vm_offset_t)mpentry));

	cluster = 0;
	for (cpu = 1; cpu < mp_ncpus; cpu++)
		aw_mc_mp_start_cpu(cpuscfg, cpuxcfg, prcm, cluster, cpu);
}