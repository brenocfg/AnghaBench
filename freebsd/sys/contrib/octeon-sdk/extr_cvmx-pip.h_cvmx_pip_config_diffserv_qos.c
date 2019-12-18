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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  qos; } ;
struct TYPE_4__ {scalar_t__ u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_pip_qos_diffx_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_PIP_QOS_DIFFX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCTEON_FEATURE_PKND ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cvmx_pip_config_diffserv_qos(uint64_t diffserv, uint64_t qos)
{
    if (octeon_has_feature(OCTEON_FEATURE_PKND))
    {
        /* FIXME for 68xx. */
    }
    else
    {
        cvmx_pip_qos_diffx_t pip_qos_diffx;
        pip_qos_diffx.u64 = 0;
        pip_qos_diffx.s.qos = qos;
        cvmx_write_csr(CVMX_PIP_QOS_DIFFX(diffserv), pip_qos_diffx.u64);
    }
}