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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  disidxalias; } ;
struct TYPE_4__ {TYPE_1__ s; int /*<<< orphan*/  u64; } ;
typedef  TYPE_2__ cvmx_l2c_ctl_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_L2C_CTL ; 
 int /*<<< orphan*/  OCTEON_CN68XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 

int cvmx_l2c_address_to_tad(uint64_t addr)
{
    uint32_t tad;
    if (OCTEON_IS_MODEL(OCTEON_CN68XX)) {
        cvmx_l2c_ctl_t l2c_ctl;
        l2c_ctl.u64 = cvmx_read_csr(CVMX_L2C_CTL);
        if (!l2c_ctl.s.disidxalias) {
            tad = ((addr >> 7) ^ (addr >> 12) ^ (addr >> 18)) & 3;
        } else {
            tad = (addr >> 7) & 3;
        }
    } else {
        tad = 0;
    }
    return tad;
}