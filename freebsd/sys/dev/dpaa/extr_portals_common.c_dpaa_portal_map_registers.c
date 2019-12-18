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
struct dpaa_portals_softc {TYPE_1__* sc_dp; int /*<<< orphan*/ * sc_rres; } ;
struct TYPE_2__ {int dp_regs_mapped; int /*<<< orphan*/  dp_ci_size; int /*<<< orphan*/  dp_ci_pa; int /*<<< orphan*/  dp_ce_size; int /*<<< orphan*/  dp_ce_pa; } ;

/* Variables and functions */
 unsigned int PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _TLB_ENTRY_IO ; 
 int /*<<< orphan*/  _TLB_ENTRY_MEM ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_pin () ; 
 int /*<<< orphan*/  sched_unpin () ; 
 int /*<<< orphan*/  tlb1_set_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dpaa_portal_map_registers(struct dpaa_portals_softc *sc)
{
	unsigned int cpu;

	sched_pin();
	cpu = PCPU_GET(cpuid);
	if (sc->sc_dp[cpu].dp_regs_mapped)
		goto out;

	tlb1_set_entry(rman_get_bushandle(sc->sc_rres[0]),
	    sc->sc_dp[cpu].dp_ce_pa, sc->sc_dp[cpu].dp_ce_size,
	    _TLB_ENTRY_MEM);
	tlb1_set_entry(rman_get_bushandle(sc->sc_rres[1]),
	    sc->sc_dp[cpu].dp_ci_pa, sc->sc_dp[cpu].dp_ci_size,
	    _TLB_ENTRY_IO);

	sc->sc_dp[cpu].dp_regs_mapped = 1;

out:
	sched_unpin();
}