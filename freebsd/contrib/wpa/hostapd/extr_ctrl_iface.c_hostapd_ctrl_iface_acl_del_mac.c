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
typedef  int /*<<< orphan*/  u8 ;
struct vlan_description {int dummy; } ;
struct mac_acl_entry {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 scalar_t__ hostapd_maclist_found (struct mac_acl_entry*,int,int /*<<< orphan*/ *,struct vlan_description*) ; 
 int /*<<< orphan*/  hostapd_remove_acl_mac (struct mac_acl_entry**,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ hwaddr_aton (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hostapd_ctrl_iface_acl_del_mac(struct mac_acl_entry **acl, int *num,
					  const char *txtaddr)
{
	u8 addr[ETH_ALEN];
	struct vlan_description vlan_id;

	if (!(*num))
		return 0;

	if (hwaddr_aton(txtaddr, addr))
		return -1;

	if (hostapd_maclist_found(*acl, *num, addr, &vlan_id))
		hostapd_remove_acl_mac(acl, num, addr);

	return 0;
}