#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mode; } ;
struct TYPE_5__ {void* u64; TYPE_1__ cn56xx; } ;
typedef  TYPE_2__ cvmx_pcsx_miscx_ctl_reg_t ;
struct TYPE_6__ {int board_type; } ;

/* Variables and functions */
#define  CVMX_BOARD_TYPE_BBGW_REF 141 
#define  CVMX_BOARD_TYPE_CN3005_EVB_HS5 140 
#define  CVMX_BOARD_TYPE_CUST_LANNER_MR955 139 
#define  CVMX_BOARD_TYPE_CUST_TNPA5651X 138 
#define  CVMX_BOARD_TYPE_CUST_TNPA56X4 137 
#define  CVMX_BOARD_TYPE_EBB5600 136 
#define  CVMX_BOARD_TYPE_EBH5600 135 
#define  CVMX_BOARD_TYPE_EBT5600 134 
#define  CVMX_BOARD_TYPE_EBT5810 133 
#define  CVMX_BOARD_TYPE_LANAI2_A 132 
#define  CVMX_BOARD_TYPE_LANAI2_G 131 
#define  CVMX_BOARD_TYPE_LANAI2_U 130 
#define  CVMX_BOARD_TYPE_NIC2E 129 
#define  CVMX_BOARD_TYPE_NIC_XLE_4G 128 
 scalar_t__ CVMX_HELPER_INTERFACE_MODE_PICMG ; 
 scalar_t__ CVMX_HELPER_INTERFACE_MODE_SGMII ; 
 scalar_t__ CVMX_HELPER_INTERFACE_MODE_SPI ; 
 int /*<<< orphan*/  CVMX_PCSX_MISCX_CTL_REG (int,int) ; 
 scalar_t__ cvmx_helper_interface_get_mode (int) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 TYPE_3__* cvmx_sysinfo_get () ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ getenv (char*) ; 

int __cvmx_helper_board_interface_probe(int interface, int supported_ports)
{
    switch (cvmx_sysinfo_get()->board_type)
    {
        case CVMX_BOARD_TYPE_CN3005_EVB_HS5:
        case CVMX_BOARD_TYPE_LANAI2_A:
        case CVMX_BOARD_TYPE_LANAI2_U:
        case CVMX_BOARD_TYPE_LANAI2_G:
            if (interface == 0)
                return 2;
	    break;
        case CVMX_BOARD_TYPE_BBGW_REF:
            if (interface == 0)
                return 2;
	    break;
        case CVMX_BOARD_TYPE_NIC_XLE_4G:
            if (interface == 0)
                return 0;
	    break;
        /* The 2nd interface on the EBH5600 is connected to the Marvel switch,
            which we don't support. Disable ports connected to it */
        case CVMX_BOARD_TYPE_EBH5600:
            if (interface == 1)
                return 0;
	    break;
        case CVMX_BOARD_TYPE_EBB5600:
#ifdef CVMX_ENABLE_PKO_FUNCTIONS
            if (cvmx_helper_interface_get_mode(interface) == CVMX_HELPER_INTERFACE_MODE_PICMG)
                return 0;
#endif
	    break;
        case CVMX_BOARD_TYPE_EBT5600:
	    /* Disable loopback.  */
	    if (interface == 3)
		return 0;
	    break;
        case CVMX_BOARD_TYPE_EBT5810:
            return 1;  /* Two ports on each SPI: 1 hooked to MAC, 1 loopback
                       ** Loopback disabled by default. */
        case CVMX_BOARD_TYPE_NIC2E:
            if (interface == 0)
                return 2;
#if defined(OCTEON_VENDOR_LANNER)
	case CVMX_BOARD_TYPE_CUST_LANNER_MR955:
	    if (interface == 1)
	        return 12;
	    break;
#endif
#if defined(OCTEON_VENDOR_GEFES)
        case CVMX_BOARD_TYPE_CUST_TNPA5651X:
                if (interface < 2) /* interface can be EITHER 0 or 1 */
			return 1;//always return 1 for XAUI and SGMII mode. 
		break;
        case CVMX_BOARD_TYPE_CUST_TNPA56X4:
		if ((interface == 0) && 
			(cvmx_helper_interface_get_mode(interface) == CVMX_HELPER_INTERFACE_MODE_SGMII))
		{
			cvmx_pcsx_miscx_ctl_reg_t pcsx_miscx_ctl_reg;
	
			/* For this port we need to set the mode to 1000BaseX */
			pcsx_miscx_ctl_reg.u64 =
				cvmx_read_csr(CVMX_PCSX_MISCX_CTL_REG(0, interface));
			pcsx_miscx_ctl_reg.cn56xx.mode = 1;
			cvmx_write_csr(CVMX_PCSX_MISCX_CTL_REG(0, interface),
						   pcsx_miscx_ctl_reg.u64);
			pcsx_miscx_ctl_reg.u64 =
				cvmx_read_csr(CVMX_PCSX_MISCX_CTL_REG(1, interface));
			pcsx_miscx_ctl_reg.cn56xx.mode = 1;
			cvmx_write_csr(CVMX_PCSX_MISCX_CTL_REG(1, interface),
						   pcsx_miscx_ctl_reg.u64);
	
			return 2;        
		} 
		break;
#endif
    }
#ifdef CVMX_BUILD_FOR_UBOOT
    if (CVMX_HELPER_INTERFACE_MODE_SPI == cvmx_helper_interface_get_mode(interface) && getenv("disable_spi"))
        return 0;
#endif
    return supported_ports;
}