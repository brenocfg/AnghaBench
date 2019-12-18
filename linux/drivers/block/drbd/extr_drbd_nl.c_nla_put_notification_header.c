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
struct drbd_notification_header {int nh_type; } ;
typedef  enum drbd_notification_type { ____Placeholder_drbd_notification_type } drbd_notification_type ;

/* Variables and functions */
 int drbd_notification_header_to_skb (struct sk_buff*,struct drbd_notification_header*,int) ; 

__attribute__((used)) static int nla_put_notification_header(struct sk_buff *msg,
				       enum drbd_notification_type type)
{
	struct drbd_notification_header nh = {
		.nh_type = type,
	};

	return drbd_notification_header_to_skb(msg, &nh, true);
}