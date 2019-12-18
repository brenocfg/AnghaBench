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
 int atoi (char const*) ; 
 int /*<<< orphan*/  hostapd_acl_comp ; 
 int hostapd_add_acl_maclist (struct mac_acl_entry**,int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostapd_maclist_found (struct mac_acl_entry*,int,int /*<<< orphan*/ *,struct vlan_description*) ; 
 scalar_t__ hwaddr_aton (char const*,int /*<<< orphan*/ *) ; 
 char* os_strstr (char const*,char*) ; 
 int /*<<< orphan*/  qsort (struct mac_acl_entry*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hostapd_ctrl_iface_acl_add_mac(struct mac_acl_entry **acl, int *num,
					  const char *cmd)
{
	u8 addr[ETH_ALEN];
	struct vlan_description vlan_id;
	int ret = 0, vlanid = 0;
	const char *pos;

	if (hwaddr_aton(cmd, addr))
		return -1;

	pos = os_strstr(cmd, "VLAN_ID=");
	if (pos)
		vlanid = atoi(pos + 8);

	if (!hostapd_maclist_found(*acl, *num, addr, &vlan_id)) {
		ret = hostapd_add_acl_maclist(acl, num, vlanid, addr);
		if (ret != -1 && *acl)
			qsort(*acl, *num, sizeof(**acl), hostapd_acl_comp);
	}

	return ret < 0 ? -1 : 0;
}