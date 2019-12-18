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
struct p2p_group_member {int /*<<< orphan*/  addr; struct p2p_group_member* next; } ;
struct p2p_group {struct p2p_group_member* members; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct p2p_group_member * p2p_group_get_client_iface(
	struct p2p_group *group, const u8 *interface_addr)
{
	struct p2p_group_member *m;

	for (m = group->members; m; m = m->next) {
		if (os_memcmp(interface_addr, m->addr, ETH_ALEN) == 0)
			return m;
	}

	return NULL;
}