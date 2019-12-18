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
struct TYPE_3__ {int /*<<< orphan*/  disidxalias; } ;
union cvmx_l2c_ctl {TYPE_1__ s; void* u64; } ;
struct TYPE_4__ {int idxalias; } ;
union cvmx_l2c_cfg {TYPE_2__ s; void* u64; } ;
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int CVMX_L2C_ALIAS_MASK ; 
 int /*<<< orphan*/  CVMX_L2C_CFG ; 
 int /*<<< orphan*/  CVMX_L2C_CTL ; 
 int CVMX_L2C_IDX_ADDR_SHIFT ; 
 int CVMX_L2C_IDX_MASK ; 
 int CVMX_L2C_MEMBANK_SELECT_SIZE ; 
 int CVMX_L2C_TAG_ADDR_ALIAS_SHIFT ; 
 int /*<<< orphan*/  OCTEON_CN68XX ; 
 int /*<<< orphan*/  OCTEON_CN6XXX ; 
 int /*<<< orphan*/  OCTEON_CNF7XXX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int cvmx_l2c_get_num_sets () ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 

uint32_t cvmx_l2c_address_to_index(uint64_t addr)
{
    uint64_t idx = addr >> CVMX_L2C_IDX_ADDR_SHIFT;
    int indxalias = 0;

    if (OCTEON_IS_MODEL(OCTEON_CN6XXX) || OCTEON_IS_MODEL(OCTEON_CNF7XXX)) {
        union cvmx_l2c_ctl l2c_ctl;
        l2c_ctl.u64 = cvmx_read_csr(CVMX_L2C_CTL);
        indxalias = !l2c_ctl.s.disidxalias;
    } else {
        union cvmx_l2c_cfg l2c_cfg;
        l2c_cfg.u64 = cvmx_read_csr(CVMX_L2C_CFG);
        indxalias = l2c_cfg.s.idxalias;
    }

    if (indxalias) {
        if (OCTEON_IS_MODEL(OCTEON_CN68XX)) {
            uint32_t a_14_12 = (idx / (CVMX_L2C_MEMBANK_SELECT_SIZE/(1<<CVMX_L2C_IDX_ADDR_SHIFT))) & 0x7;
            idx ^= (idx / cvmx_l2c_get_num_sets()) & 0x3ff;
            idx ^= a_14_12 & 0x3;
            idx ^= a_14_12 << 2; 
        } else if (OCTEON_IS_MODEL(OCTEON_CN6XXX) || OCTEON_IS_MODEL(OCTEON_CNF7XXX)) {
            uint32_t a_14_12 = (idx / (CVMX_L2C_MEMBANK_SELECT_SIZE/(1<<CVMX_L2C_IDX_ADDR_SHIFT))) & 0x7;
            idx ^= idx / cvmx_l2c_get_num_sets();
            idx ^= a_14_12;
        } else {
            idx ^= ((addr & CVMX_L2C_ALIAS_MASK) >> CVMX_L2C_TAG_ADDR_ALIAS_SHIFT);
        }
    }
    idx &= CVMX_L2C_IDX_MASK;
    return idx;
}