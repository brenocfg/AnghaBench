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
struct TYPE_3__ {int maxdram; int disable; } ;
struct TYPE_4__ {scalar_t__ u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_l2c_big_ctl_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_L2C_BIG_CTL ; 
 int CVMX_L2C_MAX_MEMSZ_ALLOWED ; 
 int /*<<< orphan*/  OCTEON_CN63XX_PASS1_X ; 
 int /*<<< orphan*/  OCTEON_CN6XXX ; 
 int /*<<< orphan*/  OCTEON_CNF7XXX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,unsigned long long,...) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 

void cvmx_l2c_set_big_size(uint64_t mem_size, int mode)
{
    if ((OCTEON_IS_MODEL(OCTEON_CN6XXX) || OCTEON_IS_MODEL(OCTEON_CNF7XXX))
         && !OCTEON_IS_MODEL(OCTEON_CN63XX_PASS1_X))
    {
        cvmx_l2c_big_ctl_t big_ctl;
        int bits = 0, zero_bits = 0;
        uint64_t mem;

        if (mem_size > (CVMX_L2C_MAX_MEMSZ_ALLOWED * 1024))
        {
            cvmx_dprintf("WARNING: Invalid memory size(%lld) requested, should be <= %lld\n",
                (unsigned long long)mem_size, (unsigned long long)CVMX_L2C_MAX_MEMSZ_ALLOWED * 1024);
            mem_size = CVMX_L2C_MAX_MEMSZ_ALLOWED * 1024;
        }

        mem = mem_size;
        while (mem)
        {
            if ((mem & 1) == 0)
                zero_bits++;
            bits++;
            mem >>= 1;
        }

        if ((bits - zero_bits) != 1 || (bits - 9) <= 0)
        {
            cvmx_dprintf("ERROR: Invalid DRAM size (%lld) requested, refer to L2C_BIG_CTL[maxdram] for valid options.\n", (unsigned long long)mem_size);
            return;
        }

        big_ctl.u64 = 0;
        big_ctl.s.maxdram = bits - 9;
        big_ctl.s.disable = mode;
        cvmx_write_csr(CVMX_L2C_BIG_CTL, big_ctl.u64);
    }
}