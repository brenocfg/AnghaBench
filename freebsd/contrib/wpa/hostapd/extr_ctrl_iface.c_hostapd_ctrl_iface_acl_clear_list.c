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
struct mac_acl_entry {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  hostapd_remove_acl_mac (struct mac_acl_entry**,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hostapd_ctrl_iface_acl_clear_list(struct mac_acl_entry **acl,
					      int *num)
{
	while (*num)
		hostapd_remove_acl_mac(acl, num, (*acl)[0].addr);
}