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
 int /*<<< orphan*/  __cvmx_spi4000_mdio_write (int,int,int,int) ; 
 int /*<<< orphan*/  cvmx_spi4000_check_speed (int,int) ; 

__attribute__((used)) static void __cvmx_spi4000_configure_phy(int interface)
{
    int port;

    /* We use separate loops below since it allows us to save a write
        to the SPI4000 for each repeated value. This adds up to a couple
        of seconds */

    /* Update the link state before resets. It takes a while for the links to
        come back after the resets. Most likely they'll come back the same as
        they are now */
    for (port=0; port < 10; port++)
        cvmx_spi4000_check_speed(interface, port);
    /* Enable RGMII DELAYS for TX_CLK and RX_CLK (see spec) */
    for (port=0; port < 10; port++)
        __cvmx_spi4000_mdio_write(interface, port, 0x14, 0x00e2);
    /* Advertise pause and 100 Full Duplex. Don't advertise half duplex or 10Mbpa */
    for (port=0; port < 10; port++)
        __cvmx_spi4000_mdio_write(interface, port, 0x4, 0x0d01);
    /* Enable PHY reset */
    for (port=0; port < 10; port++)
        __cvmx_spi4000_mdio_write(interface, port, 0x0, 0x9140);
}