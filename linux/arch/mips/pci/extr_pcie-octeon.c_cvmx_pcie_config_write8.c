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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ __cvmx_pcie_build_config_addr (int,int,int,int,int) ; 
 int /*<<< orphan*/  cvmx_write64_uint8 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cvmx_pcie_config_write8(int pcie_port, int bus, int dev, int fn,
				    int reg, uint8_t val)
{
	uint64_t address =
	    __cvmx_pcie_build_config_addr(pcie_port, bus, dev, fn, reg);
	if (address)
		cvmx_write64_uint8(address, val);
}