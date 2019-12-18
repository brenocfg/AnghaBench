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
typedef  int /*<<< orphan*/  u8 ;
struct p2p_data {TYPE_2__* go_neg_peer; } ;
struct TYPE_3__ {int /*<<< orphan*/  const* p2p_device_addr; } ;
struct TYPE_4__ {TYPE_1__ info; } ;

/* Variables and functions */

const u8 * p2p_get_go_neg_peer(struct p2p_data *p2p)
{
	if (p2p == NULL || p2p->go_neg_peer == NULL)
		return NULL;
	return p2p->go_neg_peer->info.p2p_device_addr;
}