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
struct drbd_device_state_change {int /*<<< orphan*/ * disk_state; struct drbd_device* device; } ;
struct drbd_device {int dummy; } ;
struct device_info {int /*<<< orphan*/  dev_disk_state; } ;
typedef  enum drbd_notification_type { ____Placeholder_drbd_notification_type } drbd_notification_type ;

/* Variables and functions */
 size_t NEW ; 
 int /*<<< orphan*/  notify_device_state (struct sk_buff*,unsigned int,struct drbd_device*,struct device_info*,int) ; 

void notify_device_state_change(struct sk_buff *skb,
				unsigned int seq,
				struct drbd_device_state_change *device_state_change,
				enum drbd_notification_type type)
{
	struct drbd_device *device = device_state_change->device;
	struct device_info device_info = {
		.dev_disk_state = device_state_change->disk_state[NEW],
	};

	notify_device_state(skb, seq, device, &device_info, type);
}