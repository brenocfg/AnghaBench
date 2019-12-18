#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int link; int dup; int speed; } ;
struct TYPE_17__ {TYPE_1__ s; void* u64; } ;
typedef  TYPE_3__ cvmx_pcsx_sgmx_lp_adv_reg_t ;
struct TYPE_18__ {void* u64; } ;
typedef  TYPE_4__ cvmx_pcsx_mrx_status_reg_t ;
struct TYPE_19__ {void* u64; } ;
typedef  TYPE_5__ cvmx_pcsx_miscx_ctl_reg_t ;
struct TYPE_20__ {void* u64; } ;
typedef  TYPE_6__ cvmx_pcsx_anx_adv_reg_t ;
struct TYPE_16__ {int link_up; int full_duplex; int speed; } ;
struct TYPE_21__ {scalar_t__ u64; TYPE_2__ s; } ;
typedef  TYPE_7__ cvmx_helper_link_info_t ;
struct TYPE_22__ {int board_type; scalar_t__ fdt_addr; } ;

/* Variables and functions */
#define  CVMX_BOARD_TYPE_BBGW_REF 154 
#define  CVMX_BOARD_TYPE_CN3005_EVB_HS5 153 
#define  CVMX_BOARD_TYPE_CN3010_EVB_HS5 152 
#define  CVMX_BOARD_TYPE_CN3020_EVB_HS5 151 
#define  CVMX_BOARD_TYPE_CUST_LANNER_MR320 150 
#define  CVMX_BOARD_TYPE_CUST_LANNER_MR321X 149 
#define  CVMX_BOARD_TYPE_CUST_LANNER_MR730 148 
#define  CVMX_BOARD_TYPE_CUST_NB5 147 
#define  CVMX_BOARD_TYPE_CUST_TNPA5651X 146 
#define  CVMX_BOARD_TYPE_EBB6100 145 
#define  CVMX_BOARD_TYPE_EBB6300 144 
#define  CVMX_BOARD_TYPE_EBB6600 143 
#define  CVMX_BOARD_TYPE_EBH3100 142 
#define  CVMX_BOARD_TYPE_EBH5200 141 
#define  CVMX_BOARD_TYPE_EBH5201 140 
#define  CVMX_BOARD_TYPE_EBH5600 139 
#define  CVMX_BOARD_TYPE_EBH5601 138 
#define  CVMX_BOARD_TYPE_EBH5610 137 
#define  CVMX_BOARD_TYPE_EBT5200 136 
#define  CVMX_BOARD_TYPE_EBT5600 135 
#define  CVMX_BOARD_TYPE_EP6300C 134 
#define  CVMX_BOARD_TYPE_LANAI2_A 133 
#define  CVMX_BOARD_TYPE_LANAI2_G 132 
#define  CVMX_BOARD_TYPE_LANAI2_U 131 
#define  CVMX_BOARD_TYPE_NIC2E 130 
#define  CVMX_BOARD_TYPE_NIC4E 129 
#define  CVMX_BOARD_TYPE_SIM 128 
 int CVMX_HELPER_BOARD_MGMT_IPD_PORT ; 
 int /*<<< orphan*/  CVMX_PCSX_ANX_ADV_REG (int,int) ; 
 int /*<<< orphan*/  CVMX_PCSX_MISCX_CTL_REG (int,int) ; 
 int /*<<< orphan*/  CVMX_PCSX_MRX_STATUS_REG (int,int) ; 
 int /*<<< orphan*/  CVMX_PCSX_SGMX_LP_ADV_REG (int,int) ; 
 int /*<<< orphan*/  OCTEON_CN3XXX ; 
 int /*<<< orphan*/  OCTEON_CN50XX ; 
 int /*<<< orphan*/  OCTEON_CN56XX ; 
 int /*<<< orphan*/  OCTEON_CN58XX ; 
 int /*<<< orphan*/  OCTEON_CN63XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 TYPE_7__ __cvmx_helper_board_link_get_from_dt (int) ; 
 TYPE_7__ __get_broadcom_phy_link_state (int) ; 
 TYPE_7__ __get_inband_link_state (int) ; 
 TYPE_7__ __get_marvell_phy_link_state (int) ; 
 int cvmx_helper_board_get_mii_address (int) ; 
 int cvmx_helper_get_interface_index_num (int) ; 
 int cvmx_helper_get_interface_num (int) ; 
 TYPE_7__ cvmx_override_board_link_get (int) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 TYPE_8__* cvmx_sysinfo_get () ; 

cvmx_helper_link_info_t __cvmx_helper_board_link_get(int ipd_port)
{
    cvmx_helper_link_info_t result;
    int phy_addr;
    int is_broadcom_phy = 0;

#if !defined(CVMX_BUILD_FOR_LINUX_KERNEL) && (!defined(__FreeBSD__) || !defined(_KERNEL))
    if (cvmx_sysinfo_get()->fdt_addr)
    {
        return __cvmx_helper_board_link_get_from_dt(ipd_port);
    }
#endif

    /* Give the user a chance to override the processing of this function */
    if (cvmx_override_board_link_get)
        return cvmx_override_board_link_get(ipd_port);

    /* Unless we fix it later, all links are defaulted to down */
    result.u64 = 0;

#if !defined(OCTEON_BOARD_CAPK_0100ND)
    /* This switch statement should handle all ports that either don't use
        Marvell PHYS, or don't support in-band status */
    switch (cvmx_sysinfo_get()->board_type)
    {
        case CVMX_BOARD_TYPE_SIM:
            /* The simulator gives you a simulated 1Gbps full duplex link */
            result.s.link_up = 1;
            result.s.full_duplex = 1;
            result.s.speed = 1000;
            return result;
        case CVMX_BOARD_TYPE_LANAI2_A:
        case CVMX_BOARD_TYPE_LANAI2_U:
        case CVMX_BOARD_TYPE_LANAI2_G:
            break;
        case CVMX_BOARD_TYPE_EBH3100:
        case CVMX_BOARD_TYPE_CN3010_EVB_HS5:
        case CVMX_BOARD_TYPE_CN3005_EVB_HS5:
#if !defined(OCTEON_VENDOR_GEFES)
        case CVMX_BOARD_TYPE_CN3020_EVB_HS5:
#endif
            /* Port 1 on these boards is always Gigabit */
            if (ipd_port == 1)
            {
                result.s.link_up = 1;
                result.s.full_duplex = 1;
                result.s.speed = 1000;
                return result;
            }
            /* Fall through to the generic code below */
            break;
        case CVMX_BOARD_TYPE_EBT5600:
        case CVMX_BOARD_TYPE_EBH5600:
        case CVMX_BOARD_TYPE_EBH5601:
        case CVMX_BOARD_TYPE_EBH5610:
            /* Board has 1 management ports */
            if (ipd_port == CVMX_HELPER_BOARD_MGMT_IPD_PORT)
                is_broadcom_phy = 1;
            break;
        case CVMX_BOARD_TYPE_EBH5200:
        case CVMX_BOARD_TYPE_EBH5201:
        case CVMX_BOARD_TYPE_EBT5200:
            /* Board has 2 management ports */
            if ((ipd_port >= CVMX_HELPER_BOARD_MGMT_IPD_PORT) && (ipd_port < (CVMX_HELPER_BOARD_MGMT_IPD_PORT + 2)))
                is_broadcom_phy = 1;
            break;
        case CVMX_BOARD_TYPE_EBB6100:
        case CVMX_BOARD_TYPE_EBB6300:   /* Only for MII mode, with PHY addresses 0/1. Default is RGMII*/
        case CVMX_BOARD_TYPE_EBB6600:   /* Only for MII mode, with PHY addresses 0/1. Default is RGMII*/
            if ((ipd_port >= CVMX_HELPER_BOARD_MGMT_IPD_PORT) && (ipd_port < (CVMX_HELPER_BOARD_MGMT_IPD_PORT + 2))
                && cvmx_helper_board_get_mii_address(ipd_port) >= 0 && cvmx_helper_board_get_mii_address(ipd_port) <= 1)
                is_broadcom_phy = 1;
            break;
        case CVMX_BOARD_TYPE_EP6300C:
            is_broadcom_phy = 1;
            break;
        case CVMX_BOARD_TYPE_CUST_NB5:
            /* Port 1 on these boards is always Gigabit */
            if (ipd_port == 1)
            {
                result.s.link_up = 1;
                result.s.full_duplex = 1;
                result.s.speed = 1000;
                return result;
            }
            else /* The other port uses a broadcom PHY */
                is_broadcom_phy = 1;
            break;
        case CVMX_BOARD_TYPE_BBGW_REF:
            /* Port 1 on these boards is always Gigabit */
            if (ipd_port == 2)
            {
                /* Port 2 is not hooked up */
                result.u64 = 0;
                return result;
            }
            else
            {
                /* Ports 0 and 1 connect to the switch */
                result.s.link_up = 1;
                result.s.full_duplex = 1;
                result.s.speed = 1000;
                return result;
            }
        case CVMX_BOARD_TYPE_NIC4E:
        case CVMX_BOARD_TYPE_NIC2E:
            is_broadcom_phy = 1;
            break;
	/* Private vendor-defined boards.  */
#if defined(OCTEON_VENDOR_LANNER)
	case CVMX_BOARD_TYPE_CUST_LANNER_MR730:
	    /* Ports are BCM5482S */
	    is_broadcom_phy = 1;
	    break;
	case CVMX_BOARD_TYPE_CUST_LANNER_MR320:
	case CVMX_BOARD_TYPE_CUST_LANNER_MR321X:
	    /* Port 0 connects to the switch */
	    if (ipd_port == 0)
	    {
                result.s.link_up = 1;
                result.s.full_duplex = 1;
                result.s.speed = 1000;
		return result;
	    }
	    break;
#endif
#if defined(OCTEON_VENDOR_GEFES)
	case CVMX_BOARD_TYPE_CUST_TNPA5651X:
	   /* Since we don't auto-negotiate... 1Gbps full duplex link */
	   result.s.link_up = 1;
	   result.s.full_duplex = 1;
	   result.s.speed = 1000;
	   return result;
	   break;
#endif
    }
#endif

    phy_addr = cvmx_helper_board_get_mii_address(ipd_port);
    //cvmx_dprintf("ipd_port=%d phy_addr=%d broadcom=%d\n",
    //             ipd_port, phy_addr, is_broadcom_phy);
    if (phy_addr != -1)
    {
        if (is_broadcom_phy)
        {
            result =  __get_broadcom_phy_link_state(phy_addr);
        }
        else
        {
            /* This code assumes we are using a Marvell Gigabit PHY. */
            result = __get_marvell_phy_link_state(phy_addr);
        }
    }
    else if (OCTEON_IS_MODEL(OCTEON_CN3XXX) || OCTEON_IS_MODEL(OCTEON_CN58XX)
             || OCTEON_IS_MODEL(OCTEON_CN50XX))
    {
        /* We don't have a PHY address, so attempt to use in-band status. It is
            really important that boards not supporting in-band status never get
            here. Reading broken in-band status tends to do bad things */
        result = __get_inband_link_state(ipd_port);
    }
#if defined(OCTEON_VENDOR_GEFES)
    else if( (OCTEON_IS_MODEL(OCTEON_CN56XX)) || (OCTEON_IS_MODEL(OCTEON_CN63XX)) ) 
    {
        int interface = cvmx_helper_get_interface_num(ipd_port);
        int index = cvmx_helper_get_interface_index_num(ipd_port);
        cvmx_pcsx_miscx_ctl_reg_t mode_type;
        cvmx_pcsx_mrx_status_reg_t mrx_status;
        cvmx_pcsx_anx_adv_reg_t anxx_adv;
        cvmx_pcsx_sgmx_lp_adv_reg_t sgmii_inband_status;

        anxx_adv.u64 = cvmx_read_csr(CVMX_PCSX_ANX_ADV_REG(index, interface));
        mrx_status.u64 = cvmx_read_csr(CVMX_PCSX_MRX_STATUS_REG(index, interface));

        mode_type.u64 = cvmx_read_csr(CVMX_PCSX_MISCX_CTL_REG(index, interface));

        /* Read Octeon's inband status */
        sgmii_inband_status.u64 = cvmx_read_csr(CVMX_PCSX_SGMX_LP_ADV_REG(index, interface));

        result.s.link_up = sgmii_inband_status.s.link; 
        result.s.full_duplex = sgmii_inband_status.s.dup;
        switch (sgmii_inband_status.s.speed)
        {
        case 0: /* 10 Mbps */
            result.s.speed = 10;
            break;
        case 1: /* 100 Mbps */
            result.s.speed = 100;
            break;
        case 2: /* 1 Gbps */
            result.s.speed = 1000;
            break;
        case 3: /* Illegal */
            result.s.speed = 0;
            result.s.link_up = 0;
            break;
        }
    }
#endif
    else
    {
        /* We don't have a PHY address and we don't have in-band status. There
            is no way to determine the link speed. Return down assuming this
            port isn't wired */
        result.u64 = 0;
    }

    /* If link is down, return all fields as zero. */
    if (!result.s.link_up)
        result.u64 = 0;

    return result;
}