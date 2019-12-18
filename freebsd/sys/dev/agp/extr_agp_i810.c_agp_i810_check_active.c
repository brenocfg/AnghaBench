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
typedef  int u_int8_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_I810_SMRAM ; 
 int AGP_I810_SMRAM_GMS ; 
 int AGP_I810_SMRAM_GMS_DISABLED ; 
 int ENXIO ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
agp_i810_check_active(device_t bridge_dev)
{
	u_int8_t smram;

	smram = pci_read_config(bridge_dev, AGP_I810_SMRAM, 1);
	if ((smram & AGP_I810_SMRAM_GMS) == AGP_I810_SMRAM_GMS_DISABLED)
		return (ENXIO);
	return (0);
}