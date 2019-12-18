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
#define  BDADDR_LE_PUBLIC 129 
#define  BDADDR_LE_RANDOM 128 
 int NG_HCI_LINK_ACL ; 
 int NG_HCI_LINK_LE_PUBLIC ; 
 int NG_HCI_LINK_LE_RANDOM ; 

int ng_btsock_l2cap_addrtype_to_linktype(int addrtype)
{
	switch(addrtype){
	case BDADDR_LE_PUBLIC:
		return NG_HCI_LINK_LE_PUBLIC;
	case BDADDR_LE_RANDOM:
		return NG_HCI_LINK_LE_RANDOM;
	default:
		return NG_HCI_LINK_ACL;
	}
}