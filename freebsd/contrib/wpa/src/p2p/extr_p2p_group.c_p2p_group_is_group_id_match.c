#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct p2p_group {TYPE_3__* cfg; TYPE_2__* p2p; } ;
struct TYPE_6__ {size_t ssid_len; int /*<<< orphan*/  ssid; } ;
struct TYPE_5__ {TYPE_1__* cfg; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 size_t ETH_ALEN ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,size_t) ; 

int p2p_group_is_group_id_match(struct p2p_group *group, const u8 *group_id,
				size_t group_id_len)
{
	if (group_id_len != ETH_ALEN + group->cfg->ssid_len)
		return 0;
	if (os_memcmp(group_id, group->p2p->cfg->dev_addr, ETH_ALEN) != 0)
		return 0;
	return os_memcmp(group_id + ETH_ALEN, group->cfg->ssid,
			 group->cfg->ssid_len) == 0;
}