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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPI4000_DO_READ ; 
 int /*<<< orphan*/  SPI4000_GET_READ_STATUS ; 
 int /*<<< orphan*/  SPI4000_READ_ADDRESS_HIGH ; 
 int /*<<< orphan*/  SPI4000_READ_DATA0 ; 
 int /*<<< orphan*/  SPI4000_TWSI_ID (int) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int) ; 
 int cvmx_twsi_read8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cvmx_twsix_read_ia (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_twsix_write_ia (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static uint32_t __cvmx_spi4000_read(int interface, int address)
{
    int status;
    uint64_t data;

    cvmx_twsix_write_ia(0, SPI4000_TWSI_ID(interface), SPI4000_READ_ADDRESS_HIGH, 2, 1, address);

    status = cvmx_twsi_read8(SPI4000_TWSI_ID(interface), SPI4000_DO_READ);
    while ((status == 1) || (status == 0xff))
        status = cvmx_twsi_read8(SPI4000_TWSI_ID(interface), SPI4000_GET_READ_STATUS);

    if (status)
    {
        cvmx_dprintf("SPI4000: read failed with %d\n", status);
        return 0;
    }

    status = cvmx_twsix_read_ia(0, SPI4000_TWSI_ID(interface), SPI4000_READ_DATA0, 4, 1, &data);
    if (status != 4)
    {
        cvmx_dprintf("SPI4000: read failed with %d\n", status);
        return 0;
    }

    return data;
}