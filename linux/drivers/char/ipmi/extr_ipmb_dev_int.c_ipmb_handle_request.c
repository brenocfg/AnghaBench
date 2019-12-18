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
struct ipmb_request_elem {int /*<<< orphan*/  list; int /*<<< orphan*/  request; } ;
struct ipmb_msg {int dummy; } ;
struct ipmb_dev {int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  request_queue_len; int /*<<< orphan*/  request_queue; int /*<<< orphan*/  request; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ REQUEST_QUEUE_MAX_LEN ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct ipmb_request_elem* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipmb_handle_request(struct ipmb_dev *ipmb_dev)
{
	struct ipmb_request_elem *queue_elem;

	if (atomic_read(&ipmb_dev->request_queue_len) >=
			REQUEST_QUEUE_MAX_LEN)
		return;

	queue_elem = kmalloc(sizeof(*queue_elem), GFP_ATOMIC);
	if (!queue_elem)
		return;

	memcpy(&queue_elem->request, &ipmb_dev->request,
		sizeof(struct ipmb_msg));
	list_add(&queue_elem->list, &ipmb_dev->request_queue);
	atomic_inc(&ipmb_dev->request_queue_len);
	wake_up_all(&ipmb_dev->wait_queue);
}