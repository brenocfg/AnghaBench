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
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ADD_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int CVMX_MGMT_PORT_NUM_PORTS ; 
 int /*<<< orphan*/  OCTEON_FEATURE_MGMT_PORT ; 
 int /*<<< orphan*/  octeon_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
octm_identify(driver_t *drv, device_t parent)
{
	unsigned i;

	if (!octeon_has_feature(OCTEON_FEATURE_MGMT_PORT))
		return;

	for (i = 0; i < CVMX_MGMT_PORT_NUM_PORTS; i++)
		BUS_ADD_CHILD(parent, 0, "octm", i);
}