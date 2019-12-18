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
 int /*<<< orphan*/  CVMX_ERROR_GROUP_PCI ; 
 int /*<<< orphan*/  OCTEON_FEATURE_NPEI ; 
 int __cvmx_pcie_rc_initialize_gen1 (int) ; 
 int __cvmx_pcie_rc_initialize_gen2 (int) ; 
 int /*<<< orphan*/  cvmx_error_enable_group (int /*<<< orphan*/ ,int) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 

int cvmx_pcie_rc_initialize(int pcie_port)
{
    int result;
    if (octeon_has_feature(OCTEON_FEATURE_NPEI))
        result = __cvmx_pcie_rc_initialize_gen1(pcie_port);
    else
        result = __cvmx_pcie_rc_initialize_gen2(pcie_port);
#if (!defined(CVMX_BUILD_FOR_LINUX_KERNEL) && !defined(CVMX_BUILD_FOR_FREEBSD_KERNEL)) || defined(CONFIG_CAVIUM_DECODE_RSL)
    if (result == 0)
        cvmx_error_enable_group(CVMX_ERROR_GROUP_PCI, pcie_port);
#endif
    return result;
}