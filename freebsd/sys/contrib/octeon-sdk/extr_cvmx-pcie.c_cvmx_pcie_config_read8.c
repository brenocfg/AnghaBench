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
typedef  int uint8_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ __cvmx_pcie_build_config_addr (int,int,int,int,int) ; 
 int cvmx_read64_uint8 (scalar_t__) ; 

uint8_t cvmx_pcie_config_read8(int pcie_port, int bus, int dev, int fn, int reg)
{
    uint64_t address = __cvmx_pcie_build_config_addr(pcie_port, bus, dev, fn, reg);
    if (address)
        return cvmx_read64_uint8(address);
    else
        return 0xff;
}