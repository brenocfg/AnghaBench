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
struct TYPE_3__ {int ena; } ;
struct TYPE_4__ {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_tra_ctl_t ;

/* Variables and functions */
 int CVMX_L2C_TADS ; 
 int /*<<< orphan*/  CVMX_TRAX_CTL (int) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int,int) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cvmx_tra_enable_v2(int enable, int tra)
{
    cvmx_tra_ctl_t control;

    if ((tra + 1) > CVMX_L2C_TADS)
    {
        cvmx_dprintf("cvmx_tra_enable: Invalid TRA(%d), max allowed are %d\n", tra, CVMX_L2C_TADS - 1);
        tra = 0;
    }
    control.u64 = cvmx_read_csr(CVMX_TRAX_CTL(tra));
    control.s.ena = enable;
    cvmx_write_csr(CVMX_TRAX_CTL(tra), control.u64);
    cvmx_read_csr(CVMX_TRAX_CTL(tra));
}