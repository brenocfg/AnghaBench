#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wpabuf {int dummy; } ;
struct p2p_message {int /*<<< orphan*/  device_id; } ;
struct p2p_group_member {int /*<<< orphan*/  dev_addr; struct p2p_group_member* next; } ;
struct p2p_group {struct p2p_group_member* members; TYPE_1__* p2p; } ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_3__ {TYPE_2__* cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (struct p2p_message*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ p2p_parse_p2p_ie (struct wpabuf*,struct p2p_message*) ; 

int p2p_group_match_dev_id(struct p2p_group *group, struct wpabuf *p2p)
{
	struct p2p_group_member *m;
	struct p2p_message msg;

	os_memset(&msg, 0, sizeof(msg));
	if (p2p_parse_p2p_ie(p2p, &msg))
		return 1; /* Failed to parse - assume no filter on Device ID */

	if (!msg.device_id)
		return 1; /* No filter on Device ID */

	if (os_memcmp(msg.device_id, group->p2p->cfg->dev_addr, ETH_ALEN) == 0)
		return 1; /* Match with our P2P Device Address */

	for (m = group->members; m; m = m->next) {
		if (os_memcmp(msg.device_id, m->dev_addr, ETH_ALEN) == 0)
			return 1; /* Match with group client P2P Device Address */
	}

	/* No match with Device ID */
	return 0;
}