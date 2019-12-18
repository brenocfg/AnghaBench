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
 int /*<<< orphan*/  AGP_I915_DEVEN ; 
 int AGP_I915_DEVEN_D2F0 ; 
 int AGP_I915_DEVEN_D2F0_DISABLED ; 
 int ENXIO ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
agp_i915_check_active(device_t bridge_dev)
{
	int deven;

	deven = pci_read_config(bridge_dev, AGP_I915_DEVEN, 4);
	if ((deven & AGP_I915_DEVEN_D2F0) == AGP_I915_DEVEN_D2F0_DISABLED)
		return (ENXIO);
	return (0);
}