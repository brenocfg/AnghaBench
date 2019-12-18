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
 int /*<<< orphan*/  __cvmx_spi4000_configure_mac (int) ; 
 int /*<<< orphan*/  __cvmx_spi4000_configure_phy (int) ; 
 int /*<<< orphan*/  cvmx_spi4000_is_present (int) ; 

int cvmx_spi4000_initialize(int interface)
{
    if (!cvmx_spi4000_is_present(interface))
        return -1;

    __cvmx_spi4000_configure_mac(interface);
    __cvmx_spi4000_configure_phy(interface);
    return 0;
}