#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

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
 int __cvmx_helper_loop_enable (int) ; 
 int __cvmx_helper_npi_enable (int) ; 
 int __cvmx_helper_rgmii_enable (int) ; 
 int __cvmx_helper_sgmii_enable (int) ; 
 int __cvmx_helper_spi_enable (int) ; 
 int __cvmx_helper_xaui_enable (int) ; 
 int cvmx_helper_interface_get_mode (int) ; 

__attribute__((used)) static int __cvmx_helper_packet_hardware_enable(int interface)
{
	int result = 0;
	switch (cvmx_helper_interface_get_mode(interface)) {
		/* These types don't support ports to IPD/PKO */
	case CVMX_HELPER_INTERFACE_MODE_DISABLED:
	case CVMX_HELPER_INTERFACE_MODE_PCIE:
		/* Nothing to do */
		break;
		/* XAUI is a single high speed port */
	case CVMX_HELPER_INTERFACE_MODE_XAUI:
		result = __cvmx_helper_xaui_enable(interface);
		break;
		/*
		 * RGMII/GMII/MII are all treated about the same. Most
		 * functions refer to these ports as RGMII
		 */
	case CVMX_HELPER_INTERFACE_MODE_RGMII:
	case CVMX_HELPER_INTERFACE_MODE_GMII:
		result = __cvmx_helper_rgmii_enable(interface);
		break;
		/*
		 * SPI4 can have 1-16 ports depending on the device at
		 * the other end
		 */
	case CVMX_HELPER_INTERFACE_MODE_SPI:
		result = __cvmx_helper_spi_enable(interface);
		break;
		/*
		 * SGMII can have 1-4 ports depending on how many are
		 * hooked up
		 */
	case CVMX_HELPER_INTERFACE_MODE_SGMII:
	case CVMX_HELPER_INTERFACE_MODE_PICMG:
		result = __cvmx_helper_sgmii_enable(interface);
		break;
		/* PCI target Network Packet Interface */
	case CVMX_HELPER_INTERFACE_MODE_NPI:
		result = __cvmx_helper_npi_enable(interface);
		break;
		/*
		 * Special loopback only ports. These are not the same
		 * as other ports in loopback mode
		 */
	case CVMX_HELPER_INTERFACE_MODE_LOOP:
		result = __cvmx_helper_loop_enable(interface);
		break;
	}
	return result;
}