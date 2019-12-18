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
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {int io; int did; int subdid; scalar_t__ upper; } ;
struct TYPE_4__ {scalar_t__ u64; TYPE_1__ mem; } ;
typedef  TYPE_2__ cvmx_pcie_address_t ;

/* Variables and functions */

uint64_t cvmx_pcie_get_mem_base_address(int pcie_port)
{
    cvmx_pcie_address_t pcie_addr;
    pcie_addr.u64 = 0;
    pcie_addr.mem.upper = 0;
    pcie_addr.mem.io = 1;
    pcie_addr.mem.did = 3;
    pcie_addr.mem.subdid = 3 + pcie_port;
    return pcie_addr.u64;
}