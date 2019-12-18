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
struct syscon {int dummy; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_hasprop (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rk3328_set_delays (struct syscon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk3399_set_delays (struct syscon*,int /*<<< orphan*/ ) ; 
 scalar_t__ syscon_get_by_ofw_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct syscon**) ; 

__attribute__((used)) static int
if_dwc_rk_init(device_t dev)
{
	phandle_t node;
	struct syscon *grf = NULL;

	node = ofw_bus_get_node(dev);
	if (OF_hasprop(node, "rockchip,grf") &&
	    syscon_get_by_ofw_property(dev, node,
	    "rockchip,grf", &grf) != 0) {
		device_printf(dev, "cannot get grf driver handle\n");
		return (ENXIO);
	}

#ifdef notyet
	if (ofw_bus_is_compatible(dev, "rockchip,rk3399-gmac"))
	    rk3399_set_delays(grf, node);
	else if (ofw_bus_is_compatible(dev, "rockchip,rk3328-gmac"))
	    rk3328_set_delays(grf, node);
#endif

	/* Mode should be set according to dtb property */

	return (0);
}