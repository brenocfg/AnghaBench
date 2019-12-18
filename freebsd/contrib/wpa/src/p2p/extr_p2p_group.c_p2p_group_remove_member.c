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
struct p2p_group_member {struct p2p_group_member* next; int /*<<< orphan*/  addr; } ;
struct p2p_group {int /*<<< orphan*/  num_members; struct p2p_group_member* members; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_group_free_member (struct p2p_group_member*) ; 

__attribute__((used)) static int p2p_group_remove_member(struct p2p_group *group, const u8 *addr)
{
	struct p2p_group_member *m, *prev;

	if (group == NULL)
		return 0;

	m = group->members;
	prev = NULL;
	while (m) {
		if (os_memcmp(m->addr, addr, ETH_ALEN) == 0)
			break;
		prev = m;
		m = m->next;
	}

	if (m == NULL)
		return 0;

	if (prev)
		prev->next = m->next;
	else
		group->members = m->next;
	p2p_group_free_member(m);
	group->num_members--;

	return 1;
}