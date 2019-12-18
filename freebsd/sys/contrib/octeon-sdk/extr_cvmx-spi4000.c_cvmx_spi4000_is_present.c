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
 int /*<<< orphan*/  OCTEON_CN38XX ; 
 int /*<<< orphan*/  OCTEON_CN58XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI4000_TWSI_ID (int) ; 
 int /*<<< orphan*/  SPI4000_WRITE_ADDRESS_HIGH ; 
 int /*<<< orphan*/  SPI4000_WRITE_ADDRESS_LOW ; 
 scalar_t__ cvmx_twsi_write8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* interface_is_spi4000 ; 

int cvmx_spi4000_is_present(int interface)
{
    if (!(OCTEON_IS_MODEL(OCTEON_CN38XX) || OCTEON_IS_MODEL(OCTEON_CN58XX)))
        return 0;
    // Check for the presence of a SPI4000. If it isn't there,
    // these writes will timeout.
    if (cvmx_twsi_write8(SPI4000_TWSI_ID(interface), SPI4000_WRITE_ADDRESS_HIGH, 0))
        return 0;
    if (cvmx_twsi_write8(SPI4000_TWSI_ID(interface), SPI4000_WRITE_ADDRESS_LOW, 0))
        return 0;
    interface_is_spi4000[interface] = 1;
    return 1;
}