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
struct TYPE_7__ {TYPE_2__ s; void* u64; } ;
typedef  TYPE_3__ cvmx_pescx_cfg_rd_t ;
struct TYPE_5__ {void* data; void* addr; } ;
struct TYPE_8__ {TYPE_1__ s; void* u64; } ;
typedef  TYPE_4__ cvmx_pemx_cfg_rd_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_PEMX_CFG_RD (int) ; 
 int /*<<< orphan*/  CVMX_PESCX_CFG_RD (int) ; 
 int /*<<< orphan*/  OCTEON_FEATURE_NPEI ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 

uint32_t cvmx_pcie_cfgx_read(int pcie_port, uint32_t cfg_offset)
{
    if (octeon_has_feature(OCTEON_FEATURE_NPEI))
    {
        cvmx_pescx_cfg_rd_t pescx_cfg_rd;
        pescx_cfg_rd.u64 = 0;
        pescx_cfg_rd.s.addr = cfg_offset;
        cvmx_write_csr(CVMX_PESCX_CFG_RD(pcie_port), pescx_cfg_rd.u64);
        pescx_cfg_rd.u64 = cvmx_read_csr(CVMX_PESCX_CFG_RD(pcie_port));
        return pescx_cfg_rd.s.data;
    }
    else
    {
        cvmx_pemx_cfg_rd_t pemx_cfg_rd;
        pemx_cfg_rd.u64 = 0;
        pemx_cfg_rd.s.addr = cfg_offset;
        cvmx_write_csr(CVMX_PEMX_CFG_RD(pcie_port), pemx_cfg_rd.u64);
        pemx_cfg_rd.u64 = cvmx_read_csr(CVMX_PEMX_CFG_RD(pcie_port));
        return pemx_cfg_rd.s.data;
    }
}