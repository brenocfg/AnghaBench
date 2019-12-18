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
struct opal_prd_msg_queue_item {int /*<<< orphan*/  list; int /*<<< orphan*/  msg; } ;
struct opal_prd_msg_header {int /*<<< orphan*/  size; } ;
struct opal_msg {scalar_t__ params; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned long OPAL_MSG_PRD ; 
 unsigned long OPAL_MSG_PRD2 ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct opal_prd_msg_queue_item* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  opal_prd_msg_queue ; 
 int /*<<< orphan*/  opal_prd_msg_queue_lock ; 
 int /*<<< orphan*/  opal_prd_msg_wait ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int opal_prd_msg_notifier(struct notifier_block *nb,
		unsigned long msg_type, void *_msg)
{
	struct opal_prd_msg_queue_item *item;
	struct opal_prd_msg_header *hdr;
	struct opal_msg *msg = _msg;
	int msg_size, item_size;
	unsigned long flags;

	if (msg_type != OPAL_MSG_PRD && msg_type != OPAL_MSG_PRD2)
		return 0;

	/* Calculate total size of the message and item we need to store. The
	 * 'size' field in the header includes the header itself. */
	hdr = (void *)msg->params;
	msg_size = be16_to_cpu(hdr->size);
	item_size = msg_size + sizeof(*item) - sizeof(item->msg);

	item = kzalloc(item_size, GFP_ATOMIC);
	if (!item)
		return -ENOMEM;

	memcpy(&item->msg, msg->params, msg_size);

	spin_lock_irqsave(&opal_prd_msg_queue_lock, flags);
	list_add_tail(&item->list, &opal_prd_msg_queue);
	spin_unlock_irqrestore(&opal_prd_msg_queue_lock, flags);

	wake_up_interruptible(&opal_prd_msg_wait);

	return 0;
}