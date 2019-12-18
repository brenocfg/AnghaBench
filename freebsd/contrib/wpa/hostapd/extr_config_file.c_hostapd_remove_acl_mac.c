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
struct mac_acl_entry {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_remove_in_array (struct mac_acl_entry*,int,int,int) ; 

void hostapd_remove_acl_mac(struct mac_acl_entry **acl, int *num,
			    const u8 *addr)
{
	int i = 0;

	while (i < *num) {
		if (os_memcmp((*acl)[i].addr, addr, ETH_ALEN) == 0) {
			os_remove_in_array(*acl, *num, sizeof(**acl), i);
			(*num)--;
		} else {
			i++;
		}
	}
}