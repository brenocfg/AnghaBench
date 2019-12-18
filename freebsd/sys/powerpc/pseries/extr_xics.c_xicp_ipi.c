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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ u_int ;
struct xicp_softc {scalar_t__ xics_emu; } ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ pc_hwref; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_IPI ; 
 int /*<<< orphan*/  OPAL_INT_SET_MFRR ; 
 int PSL_HV ; 
 int /*<<< orphan*/  XICP_PRIORITY ; 
 int /*<<< orphan*/  bus_write_1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct xicp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int mfmsr () ; 
 scalar_t__ opal_call (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* pcpu_find (scalar_t__) ; 
 int /*<<< orphan*/  phyp_hcall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xicp_mem_for_cpu (scalar_t__) ; 

__attribute__((used)) static void
xicp_ipi(device_t dev, u_int cpu)
{

#ifdef POWERNV
	struct xicp_softc *sc;
	cpu = pcpu_find(cpu)->pc_hwref;

	if (mfmsr() & PSL_HV) {
		sc = device_get_softc(dev);
		if (sc->xics_emu) {
			int64_t rv;
			rv = opal_call(OPAL_INT_SET_MFRR, cpu, XICP_PRIORITY);
			if (rv != 0)
			    device_printf(dev, "IPI SET_MFRR result: %ld\n", rv);
		} else
			bus_write_1(xicp_mem_for_cpu(cpu), 12, XICP_PRIORITY);
	} else
#endif
		phyp_hcall(H_IPI, (uint64_t)cpu, XICP_PRIORITY);
}