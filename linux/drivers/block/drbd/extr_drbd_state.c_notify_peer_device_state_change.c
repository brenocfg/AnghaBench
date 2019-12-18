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
struct sk_buff {int dummy; } ;
struct peer_device_info {int /*<<< orphan*/  peer_resync_susp_dependency; int /*<<< orphan*/  peer_resync_susp_peer; int /*<<< orphan*/  peer_resync_susp_user; int /*<<< orphan*/  peer_disk_state; int /*<<< orphan*/  peer_repl_state; } ;
struct drbd_peer_device_state_change {int /*<<< orphan*/ * resync_susp_dependency; int /*<<< orphan*/ * resync_susp_peer; int /*<<< orphan*/ * resync_susp_user; int /*<<< orphan*/ * disk_state; int /*<<< orphan*/ * repl_state; struct drbd_peer_device* peer_device; } ;
struct drbd_peer_device {int dummy; } ;
typedef  enum drbd_notification_type { ____Placeholder_drbd_notification_type } drbd_notification_type ;

/* Variables and functions */
 size_t NEW ; 
 int /*<<< orphan*/  notify_peer_device_state (struct sk_buff*,unsigned int,struct drbd_peer_device*,struct peer_device_info*,int) ; 

void notify_peer_device_state_change(struct sk_buff *skb,
				     unsigned int seq,
				     struct drbd_peer_device_state_change *p,
				     enum drbd_notification_type type)
{
	struct drbd_peer_device *peer_device = p->peer_device;
	struct peer_device_info peer_device_info = {
		.peer_repl_state = p->repl_state[NEW],
		.peer_disk_state = p->disk_state[NEW],
		.peer_resync_susp_user = p->resync_susp_user[NEW],
		.peer_resync_susp_peer = p->resync_susp_peer[NEW],
		.peer_resync_susp_dependency = p->resync_susp_dependency[NEW],
	};

	notify_peer_device_state(skb, seq, peer_device, &peer_device_info, type);
}