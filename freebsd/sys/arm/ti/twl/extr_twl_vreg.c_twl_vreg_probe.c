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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ twl_is_4030 (int /*<<< orphan*/ ) ; 
 scalar_t__ twl_is_6025 (int /*<<< orphan*/ ) ; 
 scalar_t__ twl_is_6030 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
twl_vreg_probe(device_t dev)
{
	if (twl_is_4030(device_get_parent(dev)))
		device_set_desc(dev, "TI TWL4030 PMIC Voltage Regulators");
	else if (twl_is_6025(device_get_parent(dev)) ||
	         twl_is_6030(device_get_parent(dev)))
		device_set_desc(dev, "TI TWL6025/TWL6030 PMIC Voltage Regulators");
	else
		return (ENXIO);

	return (0);
}