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
struct resource {int /*<<< orphan*/  r_bushandle; int /*<<< orphan*/  r_bustag; } ;
typedef  int /*<<< orphan*/  res ;

/* Variables and functions */
 int /*<<< orphan*/  AML_SOC_CBUS_BASE_ADDR ; 
 int /*<<< orphan*/  AML_SOC_HW_REV_REG ; 
 int /*<<< orphan*/  AML_SOC_METAL_REV_REG ; 
 void* aml8726_soc_hw_rev ; 
 void* aml8726_soc_metal_rev ; 
 void* bus_read_4 (struct resource*,int /*<<< orphan*/ ) ; 
 int bus_space_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_space_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fdtbus_bs_tag ; 
 int /*<<< orphan*/  memset (struct resource*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*) ; 

void
aml8726_identify_soc(void)
{
	int err;
	struct resource res;

	memset(&res, 0, sizeof(res));

	res.r_bustag = fdtbus_bs_tag;

	err = bus_space_map(res.r_bustag, AML_SOC_CBUS_BASE_ADDR, 0x100000,
	    0, &res.r_bushandle);

	if (err)
		panic("Could not allocate resource for SoC identification\n");

	aml8726_soc_hw_rev = bus_read_4(&res, AML_SOC_HW_REV_REG);

	aml8726_soc_metal_rev = bus_read_4(&res, AML_SOC_METAL_REV_REG);

	bus_space_unmap(res.r_bustag, res.r_bushandle, 0x100000);
}