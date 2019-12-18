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
typedef  scalar_t__ u_long ;
struct resource {int /*<<< orphan*/  r_bushandle; int /*<<< orphan*/  r_bustag; struct resource** res; } ;
struct aml8726_clkmsr_softc {int /*<<< orphan*/  r_bushandle; int /*<<< orphan*/  r_bustag; struct aml8726_clkmsr_softc** res; } ;
typedef  int /*<<< orphan*/  sc ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  mem ;

/* Variables and functions */
 int /*<<< orphan*/  AML_CLKMSR_CLK81 ; 
 scalar_t__ AML_SOC_HW_REV_UNKNOWN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int OF_finddevice (char*) ; 
 int /*<<< orphan*/  OF_parent (int) ; 
 int aml8726_clkmsr_clock_frequency (struct resource*,int /*<<< orphan*/ ) ; 
 scalar_t__ aml8726_soc_hw_rev ; 
 scalar_t__ bus_space_map (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int fdt_find_compatible (int,char*,int) ; 
 scalar_t__ fdt_get_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 scalar_t__ fdt_is_compatible_strict (int,char*) ; 
 scalar_t__ fdt_regsize (int,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 
 int /*<<< orphan*/  memset (struct resource*,int /*<<< orphan*/ ,int) ; 

int
aml8726_clkmsr_bus_frequency()
{
	struct resource mem;
	struct aml8726_clkmsr_softc sc;
	phandle_t node;
	u_long pbase, psize;
	u_long start, size;
	int freq;

	KASSERT(aml8726_soc_hw_rev != AML_SOC_HW_REV_UNKNOWN,
		("aml8726_soc_hw_rev isn't initialized"));

	/*
	 * Try to access the clkmsr node directly i.e. through /aliases/.
	 */

	if ((node = OF_finddevice("clkmsr")) != -1)
		if (fdt_is_compatible_strict(node, "amlogic,aml8726-clkmsr"))
			 goto moveon;

	/*
	 * Find the node the long way.
	 */
	if ((node = OF_finddevice("/soc")) == -1)
		return (0);

	if ((node = fdt_find_compatible(node,
	    "amlogic,aml8726-clkmsr", 1)) == 0)
		return (0);

moveon:
	if (fdt_get_range(OF_parent(node), 0, &pbase, &psize) != 0
	    || fdt_regsize(node, &start, &size) != 0)
		return (0);

	start += pbase;

	memset(&mem, 0, sizeof(mem));

	mem.r_bustag = fdtbus_bs_tag;

	if (bus_space_map(mem.r_bustag, start, size, 0, &mem.r_bushandle) != 0)
		return (0);

	/*
	 * Build an incomplete (however sufficient for the purpose
	 * of calling aml8726_clkmsr_clock_frequency) softc.
	 */

	memset(&sc, 0, sizeof(sc));

	sc.res[0] = &mem;

	freq = aml8726_clkmsr_clock_frequency(&sc, AML_CLKMSR_CLK81) * 1000000;

	bus_space_unmap(mem.r_bustag, mem.r_bushandle, size);

	return (freq);
}