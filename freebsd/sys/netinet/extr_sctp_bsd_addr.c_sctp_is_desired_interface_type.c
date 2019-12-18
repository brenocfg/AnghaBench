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
typedef  int uint32_t ;
struct ifnet {int if_type; } ;

/* Variables and functions */
#define  IFT_ETHER 153 
#define  IFT_FDDI 152 
#define  IFT_GIF 151 
#define  IFT_HY 150 
#define  IFT_IP 149 
#define  IFT_IPOVERCDLC 148 
#define  IFT_IPOVERCLAW 147 
#define  IFT_ISDNBASIC 146 
#define  IFT_ISDNPRIMARY 145 
#define  IFT_ISO88023 144 
#define  IFT_ISO88024 143 
#define  IFT_ISO88025 142 
#define  IFT_ISO88026 141 
#define  IFT_L2VLAN 140 
#define  IFT_LOOP 139 
#define  IFT_OTHER 138 
#define  IFT_P10 137 
#define  IFT_P80 136 
#define  IFT_PPP 135 
#define  IFT_PROPVIRTUAL 134 
#define  IFT_PTPSERIAL 133 
#define  IFT_SLIP 132 
#define  IFT_STARLAN 131 
#define  IFT_STF 130 
#define  IFT_VIRTUALIPADDRESS 129 
#define  IFT_XETHER 128 

__attribute__((used)) static uint32_t
sctp_is_desired_interface_type(struct ifnet *ifn)
{
	int result;

	/* check the interface type to see if it's one we care about */
	switch (ifn->if_type) {
	case IFT_ETHER:
	case IFT_ISO88023:
	case IFT_ISO88024:
	case IFT_ISO88025:
	case IFT_ISO88026:
	case IFT_STARLAN:
	case IFT_P10:
	case IFT_P80:
	case IFT_HY:
	case IFT_FDDI:
	case IFT_XETHER:
	case IFT_ISDNBASIC:
	case IFT_ISDNPRIMARY:
	case IFT_PTPSERIAL:
	case IFT_OTHER:
	case IFT_PPP:
	case IFT_LOOP:
	case IFT_SLIP:
	case IFT_GIF:
	case IFT_L2VLAN:
	case IFT_STF:
	case IFT_IP:
	case IFT_IPOVERCDLC:
	case IFT_IPOVERCLAW:
	case IFT_PROPVIRTUAL:	/* NetGraph Virtual too */
	case IFT_VIRTUALIPADDRESS:
		result = 1;
		break;
	default:
		result = 0;
	}

	return (result);
}