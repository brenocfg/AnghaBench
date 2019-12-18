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
 int BDADDR_BREDR ; 
 int BDADDR_LE_PUBLIC ; 
 int BDADDR_LE_RANDOM ; 
#define  NG_HCI_LINK_ACL 130 
#define  NG_HCI_LINK_LE_PUBLIC 129 
#define  NG_HCI_LINK_LE_RANDOM 128 

__attribute__((used)) static int ng_hci_linktype_to_addrtype(int linktype)
{
	switch(linktype){
	case NG_HCI_LINK_LE_PUBLIC:
		return BDADDR_LE_PUBLIC;
	case NG_HCI_LINK_LE_RANDOM:
		return BDADDR_LE_RANDOM;
	case NG_HCI_LINK_ACL:
		/*FALLTHROUGH*/
	default:
		return BDADDR_BREDR;
	}
	return BDADDR_BREDR;
}