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

/* Variables and functions */
 int /*<<< orphan*/  OCTEON_FEATURE_NPEI ; 
 int __cvmx_pcie_rc_initialize_gen1 (int) ; 
 int __cvmx_pcie_rc_initialize_gen2 (int) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cvmx_pcie_rc_initialize(int pcie_port)
{
	int result;
	if (octeon_has_feature(OCTEON_FEATURE_NPEI))
		result = __cvmx_pcie_rc_initialize_gen1(pcie_port);
	else
		result = __cvmx_pcie_rc_initialize_gen2(pcie_port);
	return result;
}