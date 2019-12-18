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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int untagged; int notempty; } ;
struct mac_acl_entry {TYPE_1__ vlan_id; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 struct mac_acl_entry* os_realloc_array (struct mac_acl_entry*,int,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int hostapd_add_acl_maclist(struct mac_acl_entry **acl, int *num,
			    int vlan_id, const u8 *addr)
{
	struct mac_acl_entry *newacl;

	newacl = os_realloc_array(*acl, *num + 1, sizeof(**acl));
	if (!newacl) {
		wpa_printf(MSG_ERROR, "MAC list reallocation failed");
		return -1;
	}

	*acl = newacl;
	os_memcpy((*acl)[*num].addr, addr, ETH_ALEN);
	os_memset(&(*acl)[*num].vlan_id, 0, sizeof((*acl)[*num].vlan_id));
	(*acl)[*num].vlan_id.untagged = vlan_id;
	(*acl)[*num].vlan_id.notempty = !!vlan_id;
	(*num)++;

	return 0;
}