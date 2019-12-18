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
 int /*<<< orphan*/  __cvmx_spi4000_write (int,int,int) ; 

__attribute__((used)) static void __cvmx_spi4000_mdio_write(int interface, int port, int location, int val)
{
    static int last_value=-1;
    mdio_single_command_t mdio;

    mdio.u32 = 0;
    mdio.s.mdi_command = 1;
    mdio.s.op_code = 1;
    mdio.s.phy_address = port;
    mdio.s.reg_address = location;

    /* Since the TWSI accesses are very slow, don't update the write value
        if it is the same as the last value */
    if (val != last_value)
    {
        last_value = val;
        __cvmx_spi4000_write(interface, 0x0681, val);
    }

    __cvmx_spi4000_write(interface, 0x0680, mdio.u32);
}