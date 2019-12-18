#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ srio; } ;
struct TYPE_10__ {TYPE_2__ s; void* u64; } ;
typedef  TYPE_4__ cvmx_sriox_status_reg_t ;
struct TYPE_9__ {int qlm_spd; int qlm_cfg; } ;
struct TYPE_11__ {TYPE_3__ s; void* u64; } ;
typedef  TYPE_5__ cvmx_mio_qlmx_cfg_t ;
struct TYPE_7__ {int speed; scalar_t__ mode; } ;
struct TYPE_12__ {TYPE_1__ s; void* u64; } ;
typedef  TYPE_6__ cvmx_gmxx_inf_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_INF_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_MIO_QLMX_CFG (int) ; 
 int /*<<< orphan*/  CVMX_SRIOX_STATUS_REG (int) ; 
 int /*<<< orphan*/  OCTEON_CN61XX ; 
 int /*<<< orphan*/  OCTEON_CN63XX ; 
 int /*<<< orphan*/  OCTEON_CN66XX ; 
 int /*<<< orphan*/  OCTEON_CN66XX_PASS1_0 ; 
 int /*<<< orphan*/  OCTEON_CN68XX ; 
 int /*<<< orphan*/  OCTEON_CNF71XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 

int cvmx_qlm_get_status(int qlm)
{
    cvmx_mio_qlmx_cfg_t qlmx_cfg;

    if (OCTEON_IS_MODEL(OCTEON_CN68XX))
    {
        qlmx_cfg.u64 = cvmx_read_csr(CVMX_MIO_QLMX_CFG(qlm));
        /* QLM is disabled when QLM SPD is 15. */
        if (qlmx_cfg.s.qlm_spd == 15)
            return  -1;

        switch (qlmx_cfg.s.qlm_cfg)
        {
            case 0: /* PCIE */
                return 3;
            case 1: /* ILK */
                return 9;
            case 2: /* SGMII */
                return 1;
            case 3: /* XAUI */
                return 2;
            case 7: /* RXAUI */
                return 10;
            default: return -1;
        }
    }
    else if (OCTEON_IS_MODEL(OCTEON_CN66XX))
    {
        qlmx_cfg.u64 = cvmx_read_csr(CVMX_MIO_QLMX_CFG(qlm));
        /* QLM is disabled when QLM SPD is 15. */
        if (qlmx_cfg.s.qlm_spd == 15)
            return  -1;

        switch (qlmx_cfg.s.qlm_cfg)
        {
            case 0x9: /* SGMII */
                return 1;
            case 0xb: /* XAUI */
                return 2;
            case 0x0: /* PCIE gen2 */
            case 0x8: /* PCIE gen2 (alias) */
            case 0x2: /* PCIE gen1 */
            case 0xa: /* PCIE gen1 (alias) */
                return 3;
            case 0x1: /* SRIO 1x4 short */
            case 0x3: /* SRIO 1x4 long */
                return 4;
            case 0x4: /* SRIO 2x2 short */
            case 0x6: /* SRIO 2x2 long */
                return 5;
            case 0x5: /* SRIO 4x1 short */
            case 0x7: /* SRIO 4x1 long */
                if (!OCTEON_IS_MODEL(OCTEON_CN66XX_PASS1_0))
                    return 6;
            default:
                return -1;
        }
    }
    else if (OCTEON_IS_MODEL(OCTEON_CN63XX))
    {
        cvmx_sriox_status_reg_t status_reg;
        /* For now skip qlm2 */
        if (qlm == 2)
        {
            cvmx_gmxx_inf_mode_t inf_mode;
            inf_mode.u64 = cvmx_read_csr(CVMX_GMXX_INF_MODE(0));
            if (inf_mode.s.speed == 15) 
                return -1;
            else if(inf_mode.s.mode == 0)
                return 1;
            else
                return 2;
        }
        status_reg.u64 = cvmx_read_csr(CVMX_SRIOX_STATUS_REG(qlm));
        if (status_reg.s.srio)
            return 4;
        else
            return 3;
    }
    else if (OCTEON_IS_MODEL(OCTEON_CN61XX))
    {
        qlmx_cfg.u64 = cvmx_read_csr(CVMX_MIO_QLMX_CFG(qlm));
        /* QLM is disabled when QLM SPD is 15. */
        if (qlmx_cfg.s.qlm_spd == 15)
            return  -1;

        switch(qlm)
        {
            case 0:
                switch (qlmx_cfg.s.qlm_cfg)
                {
                    case 0: /* PCIe 1x4 gen2 / gen1 */
                        return 3;
                    case 2: /* SGMII */
                        return 1;
                    case 3: /* XAUI */
                        return 2;
                    default: return -1;
                }
                break;
            case 1:
                switch (qlmx_cfg.s.qlm_cfg)
                {
                    case 0: /* PCIe 1x2 gen2 / gen1 */
                        return 7;
                    case 1: /* PCIe 2x1 gen2 / gen1 */
                        return 8;
                    default: return -1;
                }
                break;
            case 2:
                switch (qlmx_cfg.s.qlm_cfg)
                {
                    case 2: /* SGMII */
                        return 1;
                    case 3: /* XAUI */
                        return 2;
                    default: return -1;
                }
                break;
        }
    }
    else if (OCTEON_IS_MODEL(OCTEON_CNF71XX))
    {
        qlmx_cfg.u64 = cvmx_read_csr(CVMX_MIO_QLMX_CFG(qlm));
        /* QLM is disabled when QLM SPD is 15. */
        if (qlmx_cfg.s.qlm_spd == 15)
            return  -1;

        switch(qlm)
        {
            case 0:
                if (qlmx_cfg.s.qlm_cfg == 2) /* SGMII */
                    return 1;
                break;
            case 1:
                switch (qlmx_cfg.s.qlm_cfg)
                {
                    case 0: /* PCIe 1x2 gen2 / gen1 */
                        return 7;
                    case 1: /* PCIe 2x1 gen2 / gen1 */
                        return 8;
                    default: return -1;
                }
                break;
        }
    }
    return -1;
}