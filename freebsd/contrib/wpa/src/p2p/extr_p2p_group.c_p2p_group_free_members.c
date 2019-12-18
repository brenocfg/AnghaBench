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
struct p2p_group_member {struct p2p_group_member* next; } ;
struct p2p_group {scalar_t__ num_members; struct p2p_group_member* members; } ;

/* Variables and functions */
 int /*<<< orphan*/  p2p_group_free_member (struct p2p_group_member*) ; 

__attribute__((used)) static void p2p_group_free_members(struct p2p_group *group)
{
	struct p2p_group_member *m, *prev;
	m = group->members;
	group->members = NULL;
	group->num_members = 0;
	while (m) {
		prev = m;
		m = m->next;
		p2p_group_free_member(prev);
	}
}