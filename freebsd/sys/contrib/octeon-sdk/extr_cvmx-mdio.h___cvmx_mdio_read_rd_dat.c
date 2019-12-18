#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_4__ {scalar_t__ pending; } ;
struct TYPE_5__ {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_smix_rd_dat_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CLOCK_CORE ; 
 scalar_t__ CVMX_MDIO_TIMEOUT ; 
 int /*<<< orphan*/  CVMX_SMIX_RD_DAT (int) ; 
 int cvmx_clock_get_rate (int /*<<< orphan*/ ) ; 
 int cvmx_get_cycle () ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_wait (int) ; 

__attribute__((used)) static inline cvmx_smix_rd_dat_t __cvmx_mdio_read_rd_dat(int bus_id)
{
    cvmx_smix_rd_dat_t smi_rd;
    uint64_t done = cvmx_get_cycle() + (uint64_t)CVMX_MDIO_TIMEOUT *
                       cvmx_clock_get_rate(CVMX_CLOCK_CORE) / 1000000;
    do
    {
        cvmx_wait(1000);
        smi_rd.u64 = cvmx_read_csr(CVMX_SMIX_RD_DAT(bus_id));
    } while (smi_rd.s.pending && (cvmx_get_cycle() < done));
    return smi_rd;
}