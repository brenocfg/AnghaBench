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
typedef  enum wpa_driver_if_type { ____Placeholder_wpa_driver_if_type } wpa_driver_if_type ;

/* Variables and functions */
#define  P2P_GROUP_INTERFACE_CLIENT 130 
#define  P2P_GROUP_INTERFACE_GO 129 
#define  P2P_GROUP_INTERFACE_PENDING 128 
 int WPA_IF_P2P_CLIENT ; 
 int WPA_IF_P2P_GO ; 
 int WPA_IF_P2P_GROUP ; 

__attribute__((used)) static enum wpa_driver_if_type wpas_p2p_if_type(int p2p_group_interface)
{
	switch (p2p_group_interface) {
	case P2P_GROUP_INTERFACE_PENDING:
		return WPA_IF_P2P_GROUP;
	case P2P_GROUP_INTERFACE_GO:
		return WPA_IF_P2P_GO;
	case P2P_GROUP_INTERFACE_CLIENT:
		return WPA_IF_P2P_CLIENT;
	}

	return WPA_IF_P2P_GROUP;
}