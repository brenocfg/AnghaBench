#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int board_type; } ;

/* Variables and functions */
#define  CVMX_BOARD_TYPE_BBGW_REF 156 
#define  CVMX_BOARD_TYPE_CN3005_EVB_HS5 155 
#define  CVMX_BOARD_TYPE_CN3010_EVB_HS5 154 
#define  CVMX_BOARD_TYPE_CN3020_EVB_HS5 153 
#define  CVMX_BOARD_TYPE_CUST_NB5 152 
#define  CVMX_BOARD_TYPE_CUST_WSX16 151 
#define  CVMX_BOARD_TYPE_EBH3000 150 
#define  CVMX_BOARD_TYPE_EBH3100 149 
#define  CVMX_BOARD_TYPE_EBH5200 148 
#define  CVMX_BOARD_TYPE_EBH5201 147 
#define  CVMX_BOARD_TYPE_EBH5600 146 
#define  CVMX_BOARD_TYPE_EBH5601 145 
#define  CVMX_BOARD_TYPE_EBH5610 144 
#define  CVMX_BOARD_TYPE_EBT3000 143 
#define  CVMX_BOARD_TYPE_EBT5200 142 
#define  CVMX_BOARD_TYPE_EBT5800 141 
#define  CVMX_BOARD_TYPE_HIKARI 140 
#define  CVMX_BOARD_TYPE_KODAMA 139 
#define  CVMX_BOARD_TYPE_KONTRON_S1901 138 
#define  CVMX_BOARD_TYPE_NAC38 137 
#define  CVMX_BOARD_TYPE_NIC10E 136 
#define  CVMX_BOARD_TYPE_NIC2E 135 
#define  CVMX_BOARD_TYPE_NIC4E 134 
#define  CVMX_BOARD_TYPE_NICPRO2 133 
#define  CVMX_BOARD_TYPE_NIC_XLE_10G 132 
#define  CVMX_BOARD_TYPE_NIC_XLE_4G 131 
#define  CVMX_BOARD_TYPE_SIM 130 
#define  CVMX_BOARD_TYPE_THUNDER 129 
#define  CVMX_BOARD_TYPE_UBNT_E100 128 
 int CVMX_HELPER_BOARD_MGMT_IPD_PORT ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int) ; 
 TYPE_1__* cvmx_sysinfo_get () ; 

int cvmx_helper_board_get_mii_address(int ipd_port)
{
	switch (cvmx_sysinfo_get()->board_type) {
	case CVMX_BOARD_TYPE_SIM:
		/* Simulator doesn't have MII */
		return -1;
	case CVMX_BOARD_TYPE_EBT3000:
	case CVMX_BOARD_TYPE_EBT5800:
	case CVMX_BOARD_TYPE_THUNDER:
	case CVMX_BOARD_TYPE_NICPRO2:
		/* Interface 0 is SPI4, interface 1 is RGMII */
		if ((ipd_port >= 16) && (ipd_port < 20))
			return ipd_port - 16;
		else
			return -1;
	case CVMX_BOARD_TYPE_KODAMA:
	case CVMX_BOARD_TYPE_EBH3100:
	case CVMX_BOARD_TYPE_HIKARI:
	case CVMX_BOARD_TYPE_CN3010_EVB_HS5:
	case CVMX_BOARD_TYPE_CN3005_EVB_HS5:
	case CVMX_BOARD_TYPE_CN3020_EVB_HS5:
		/*
		 * Port 0 is WAN connected to a PHY, Port 1 is GMII
		 * connected to a switch
		 */
		if (ipd_port == 0)
			return 4;
		else if (ipd_port == 1)
			return 9;
		else
			return -1;
	case CVMX_BOARD_TYPE_NAC38:
		/* Board has 8 RGMII ports PHYs are 0-7 */
		if ((ipd_port >= 0) && (ipd_port < 4))
			return ipd_port;
		else if ((ipd_port >= 16) && (ipd_port < 20))
			return ipd_port - 16 + 4;
		else
			return -1;
	case CVMX_BOARD_TYPE_EBH3000:
		/* Board has dual SPI4 and no PHYs */
		return -1;
	case CVMX_BOARD_TYPE_EBH5200:
	case CVMX_BOARD_TYPE_EBH5201:
	case CVMX_BOARD_TYPE_EBT5200:
		/* Board has 2 management ports */
		if ((ipd_port >= CVMX_HELPER_BOARD_MGMT_IPD_PORT) &&
		    (ipd_port < (CVMX_HELPER_BOARD_MGMT_IPD_PORT + 2)))
			return ipd_port - CVMX_HELPER_BOARD_MGMT_IPD_PORT;
		/*
		 * Board has 4 SGMII ports. The PHYs start right after the MII
		 * ports MII0 = 0, MII1 = 1, SGMII = 2-5.
		 */
		if ((ipd_port >= 0) && (ipd_port < 4))
			return ipd_port + 2;
		else
			return -1;
	case CVMX_BOARD_TYPE_EBH5600:
	case CVMX_BOARD_TYPE_EBH5601:
	case CVMX_BOARD_TYPE_EBH5610:
		/* Board has 1 management port */
		if (ipd_port == CVMX_HELPER_BOARD_MGMT_IPD_PORT)
			return 0;
		/*
		 * Board has 8 SGMII ports. 4 connect out, two connect
		 * to a switch, and 2 loop to each other
		 */
		if ((ipd_port >= 0) && (ipd_port < 4))
			return ipd_port + 1;
		else
			return -1;
	case CVMX_BOARD_TYPE_CUST_NB5:
		if (ipd_port == 2)
			return 4;
		else
			return -1;
	case CVMX_BOARD_TYPE_NIC_XLE_4G:
		/* Board has 4 SGMII ports. connected QLM3(interface 1) */
		if ((ipd_port >= 16) && (ipd_port < 20))
			return ipd_port - 16 + 1;
		else
			return -1;
	case CVMX_BOARD_TYPE_NIC_XLE_10G:
	case CVMX_BOARD_TYPE_NIC10E:
		return -1;
	case CVMX_BOARD_TYPE_NIC4E:
		if (ipd_port >= 0 && ipd_port <= 3)
			return (ipd_port + 0x1f) & 0x1f;
		else
			return -1;
	case CVMX_BOARD_TYPE_NIC2E:
		if (ipd_port >= 0 && ipd_port <= 1)
			return ipd_port + 1;
		else
			return -1;
	case CVMX_BOARD_TYPE_BBGW_REF:
		/*
		 * No PHYs are connected to Octeon, everything is
		 * through switch.
		 */
		return -1;

	case CVMX_BOARD_TYPE_CUST_WSX16:
		if (ipd_port >= 0 && ipd_port <= 3)
			return ipd_port;
		else if (ipd_port >= 16 && ipd_port <= 19)
			return ipd_port - 16 + 4;
		else
			return -1;
	case CVMX_BOARD_TYPE_UBNT_E100:
		if (ipd_port >= 0 && ipd_port <= 2)
			return 7 - ipd_port;
		else
			return -1;
	case CVMX_BOARD_TYPE_KONTRON_S1901:
		if (ipd_port == CVMX_HELPER_BOARD_MGMT_IPD_PORT)
			return 1;
		else
			return -1;

	}

	/* Some unknown board. Somebody forgot to update this function... */
	cvmx_dprintf
	    ("cvmx_helper_board_get_mii_address: Unknown board type %d\n",
	     cvmx_sysinfo_get()->board_type);
	return -1;
}