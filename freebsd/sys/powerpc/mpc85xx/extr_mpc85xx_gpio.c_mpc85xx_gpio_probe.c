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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  SPR_SVR ; 
#define  SVR_MPC8533 129 
#define  SVR_MPC8533E 128 
 int SVR_VER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_status_okay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpc85xx_gpio_probe(device_t dev)
{
	uint32_t svr;

	if (!ofw_bus_status_okay(dev))
		return (ENXIO);

	if (!ofw_bus_is_compatible(dev, "gpio"))
		return (ENXIO);

	svr = mfspr(SPR_SVR);
	switch (SVR_VER(svr)) {
	case SVR_MPC8533:
	case SVR_MPC8533E:
		break;
	default:
		return (ENXIO);
	}

	device_set_desc(dev, "MPC85xx GPIO driver");
	return (0);
}