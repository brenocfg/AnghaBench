#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_6__ {void* data; void* addr; } ;
struct TYPE_7__ {scalar_t__ u64; TYPE_2__ s; } ;
typedef  TYPE_3__ cvmx_pescx_cfg_wr_t ;
struct TYPE_5__ {void* data; void* addr; } ;
struct TYPE_8__ {scalar_t__ u64; TYPE_1__ s; } ;
typedef  TYPE_4__ cvmx_pemx_cfg_wr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_PEMX_CFG_WR (int) ; 
 int /*<<< orphan*/  CVMX_PESCX_CFG_WR (int) ; 
 int /*<<< orphan*/  OCTEON_FEATURE_NPEI ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 

void cvmx_pcie_cfgx_write(int pcie_port, uint32_t cfg_offset, uint32_t val)
{
    if (octeon_has_feature(OCTEON_FEATURE_NPEI))
    {
        cvmx_pescx_cfg_wr_t pescx_cfg_wr;
        pescx_cfg_wr.u64 = 0;
        pescx_cfg_wr.s.addr = cfg_offset;
        pescx_cfg_wr.s.data = val;
        cvmx_write_csr(CVMX_PESCX_CFG_WR(pcie_port), pescx_cfg_wr.u64);
    }
    else
    {
        cvmx_pemx_cfg_wr_t pemx_cfg_wr;
        pemx_cfg_wr.u64 = 0;
        pemx_cfg_wr.s.addr = cfg_offset;
        pemx_cfg_wr.s.data = val;
        cvmx_write_csr(CVMX_PEMX_CFG_WR(pcie_port), pemx_cfg_wr.u64);
    }
}