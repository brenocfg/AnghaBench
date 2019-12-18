#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int io; int did; int subdid; scalar_t__ upper; } ;
union cvmx_pcie_address {scalar_t__ u64; TYPE_1__ mem; } ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */

__attribute__((used)) static inline uint64_t cvmx_pcie_get_mem_base_address(int pcie_port)
{
	union cvmx_pcie_address pcie_addr;
	pcie_addr.u64 = 0;
	pcie_addr.mem.upper = 0;
	pcie_addr.mem.io = 1;
	pcie_addr.mem.did = 3;
	pcie_addr.mem.subdid = 3 + pcie_port;
	return pcie_addr.u64;
}