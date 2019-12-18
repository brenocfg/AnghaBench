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
#define  IFT_BRIDGE 134 
#define  IFT_ETHER 133 
#define  IFT_FDDI 132 
#define  IFT_INFINIBAND 131 
#define  IFT_ISO88023 130 
#define  IFT_ISO88024 129 
#define  IFT_L2VLAN 128 

__attribute__((used)) static int
valid_type(int type)
{

	switch (type) {
	case IFT_ETHER:
	case IFT_FDDI:
	case IFT_INFINIBAND:
	case IFT_ISO88023:
	case IFT_ISO88024:
	case IFT_L2VLAN:
	case IFT_BRIDGE:
		return (1);
	default:
		return (0);
	}
}