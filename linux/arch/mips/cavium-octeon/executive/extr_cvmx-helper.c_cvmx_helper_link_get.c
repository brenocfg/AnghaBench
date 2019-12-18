#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int full_duplex; int link_up; int speed; } ;
struct TYPE_9__ {TYPE_1__ s; scalar_t__ u64; } ;
typedef  TYPE_2__ cvmx_helper_link_info_t ;

/* Variables and functions */
#define  CVMX_HELPER_INTERFACE_MODE_DISABLED 137 
#define  CVMX_HELPER_INTERFACE_MODE_GMII 136 
#define  CVMX_HELPER_INTERFACE_MODE_LOOP 135 
#define  CVMX_HELPER_INTERFACE_MODE_NPI 134 
#define  CVMX_HELPER_INTERFACE_MODE_PCIE 133 
#define  CVMX_HELPER_INTERFACE_MODE_PICMG 132 
#define  CVMX_HELPER_INTERFACE_MODE_RGMII 131 
#define  CVMX_HELPER_INTERFACE_MODE_SGMII 130 
#define  CVMX_HELPER_INTERFACE_MODE_SPI 129 
#define  CVMX_HELPER_INTERFACE_MODE_XAUI 128 
 int /*<<< orphan*/  WARN (int,char*) ; 
 TYPE_2__ __cvmx_helper_rgmii_link_get (int) ; 
 TYPE_2__ __cvmx_helper_sgmii_link_get (int) ; 
 TYPE_2__ __cvmx_helper_spi_link_get (int) ; 
 TYPE_2__ __cvmx_helper_xaui_link_get (int) ; 
 int cvmx_helper_get_interface_index_num (int) ; 
 int cvmx_helper_get_interface_num (int) ; 
 int cvmx_helper_interface_get_mode (int) ; 
 int cvmx_helper_ports_on_interface (int) ; 

cvmx_helper_link_info_t cvmx_helper_link_get(int ipd_port)
{
	cvmx_helper_link_info_t result;
	int interface = cvmx_helper_get_interface_num(ipd_port);
	int index = cvmx_helper_get_interface_index_num(ipd_port);

	/* The default result will be a down link unless the code below
	   changes it */
	result.u64 = 0;

	if (index >= cvmx_helper_ports_on_interface(interface))
		return result;

	switch (cvmx_helper_interface_get_mode(interface)) {
	case CVMX_HELPER_INTERFACE_MODE_DISABLED:
	case CVMX_HELPER_INTERFACE_MODE_PCIE:
		/* Network links are not supported */
		break;
	case CVMX_HELPER_INTERFACE_MODE_XAUI:
		result = __cvmx_helper_xaui_link_get(ipd_port);
		break;
	case CVMX_HELPER_INTERFACE_MODE_GMII:
		if (index == 0)
			result = __cvmx_helper_rgmii_link_get(ipd_port);
		else {
			WARN(1, "Using deprecated link status - please update your DT");
			result.s.full_duplex = 1;
			result.s.link_up = 1;
			result.s.speed = 1000;
		}
		break;
	case CVMX_HELPER_INTERFACE_MODE_RGMII:
		result = __cvmx_helper_rgmii_link_get(ipd_port);
		break;
	case CVMX_HELPER_INTERFACE_MODE_SPI:
		result = __cvmx_helper_spi_link_get(ipd_port);
		break;
	case CVMX_HELPER_INTERFACE_MODE_SGMII:
	case CVMX_HELPER_INTERFACE_MODE_PICMG:
		result = __cvmx_helper_sgmii_link_get(ipd_port);
		break;
	case CVMX_HELPER_INTERFACE_MODE_NPI:
	case CVMX_HELPER_INTERFACE_MODE_LOOP:
		/* Network links are not supported */
		break;
	}
	return result;
}