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
struct urb {int dummy; } ;
struct sk_buff {scalar_t__ cb; } ;
struct bfusb_data_scb {struct urb* urb; } ;
struct bfusb_data {int /*<<< orphan*/  completed_q; int /*<<< orphan*/  pending_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct bfusb_data*) ; 
 struct urb* bfusb_get_completed (struct bfusb_data*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 

__attribute__((used)) static void bfusb_unlink_urbs(struct bfusb_data *data)
{
	struct sk_buff *skb;
	struct urb *urb;

	BT_DBG("bfusb %p", data);

	while ((skb = skb_dequeue(&data->pending_q))) {
		urb = ((struct bfusb_data_scb *) skb->cb)->urb;
		usb_kill_urb(urb);
		skb_queue_tail(&data->completed_q, skb);
	}

	while ((urb = bfusb_get_completed(data)))
		usb_free_urb(urb);
}