#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_5__ {int /*<<< orphan*/  u64; } ;
typedef  TYPE_1__ cvmx_pip_prt_tagx_t ;
struct TYPE_6__ {int /*<<< orphan*/  u64; } ;
typedef  TYPE_2__ cvmx_pip_prt_cfgx_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_PIP_PRT_CFGX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_PRT_TAGX (int) ; 
 int /*<<< orphan*/  OCTEON_FEATURE_PKND ; 
 int cvmx_helper_get_interface_index_num (int) ; 
 int cvmx_helper_get_interface_num (int) ; 
 int cvmx_helper_get_pknd (int,int) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cvmx_pip_config_port(uint64_t port_num,
                                        cvmx_pip_prt_cfgx_t port_cfg,
                                        cvmx_pip_prt_tagx_t port_tag_cfg)
{

    if (octeon_has_feature(OCTEON_FEATURE_PKND))
    {
        int interface, index, pknd;

        interface = cvmx_helper_get_interface_num(port_num);
        index = cvmx_helper_get_interface_index_num(port_num);
	pknd = cvmx_helper_get_pknd(interface, index);

	port_num = pknd; /* overload port_num with pknd */
    }

    cvmx_write_csr(CVMX_PIP_PRT_CFGX(port_num), port_cfg.u64);
    cvmx_write_csr(CVMX_PIP_PRT_TAGX(port_num), port_tag_cfg.u64);
}