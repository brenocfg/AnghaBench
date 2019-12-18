#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mdi_command; int op_code; int phy_address; int reg_address; } ;
struct TYPE_4__ {int u32; TYPE_1__ s; } ;
typedef  TYPE_2__ mdio_single_command_t ;

/* Variables and functions */
 int __cvmx_spi4000_read (int,int) ; 
 int /*<<< orphan*/  __cvmx_spi4000_write (int,int,int) ; 

__attribute__((used)) static int __cvmx_spi4000_mdio_read(int interface, int port, int location)
{
    mdio_single_command_t mdio;

    mdio.u32 = 0;
    mdio.s.mdi_command = 1;
    mdio.s.op_code = 2;
    mdio.s.phy_address = port;
    mdio.s.reg_address = location;
    __cvmx_spi4000_write(interface, 0x0680, mdio.u32);

    do
    {
        mdio.u32 = __cvmx_spi4000_read(interface, 0x0680);
    } while (mdio.s.mdi_command);

    return __cvmx_spi4000_read(interface, 0x0681) >> 16;
}