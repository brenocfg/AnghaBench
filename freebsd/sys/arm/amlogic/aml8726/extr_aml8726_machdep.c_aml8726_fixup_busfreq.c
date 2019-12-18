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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  prop ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  scalar_t__ pcell_t ;
typedef  int /*<<< orphan*/  freq ;

/* Variables and functions */
 int /*<<< orphan*/  OF_finddevice (char*) ; 
 int OF_getencprop (int /*<<< orphan*/ ,char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  OF_setprop (int /*<<< orphan*/ ,char*,void*,int) ; 
 scalar_t__ aml8726_clkmsr_bus_frequency () ; 
 scalar_t__ cpu_to_fdt32 (scalar_t__) ; 
 scalar_t__ fdt_is_compatible_strict (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
aml8726_fixup_busfreq(void)
{
	phandle_t node;
	pcell_t freq, prop;
	ssize_t len;

	/*
	 * Set the bus-frequency for the SoC simple-bus if it
	 * needs updating (meaning the current frequency is zero).
	 */

	if ((freq = aml8726_clkmsr_bus_frequency()) == 0 ||
	    (node = OF_finddevice("/soc")) == 0 ||
	    fdt_is_compatible_strict(node, "simple-bus") == 0)
		while (1);

	freq = cpu_to_fdt32(freq);

	len = OF_getencprop(node, "bus-frequency", &prop, sizeof(prop));
	if ((len / sizeof(prop)) == 1 && prop == 0)
		OF_setprop(node, "bus-frequency", (void *)&freq, sizeof(freq));
}