#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_dmac_desc {unsigned int sg_allocated_len; int /*<<< orphan*/  node; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct usb_dmac_chan {TYPE_1__ vc; int /*<<< orphan*/  desc_freed; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct usb_dmac_desc* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  struct_size (struct usb_dmac_desc*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int usb_dmac_desc_alloc(struct usb_dmac_chan *chan, unsigned int sg_len,
			       gfp_t gfp)
{
	struct usb_dmac_desc *desc;
	unsigned long flags;

	desc = kzalloc(struct_size(desc, sg, sg_len), gfp);
	if (!desc)
		return -ENOMEM;

	desc->sg_allocated_len = sg_len;
	INIT_LIST_HEAD(&desc->node);

	spin_lock_irqsave(&chan->vc.lock, flags);
	list_add_tail(&desc->node, &chan->desc_freed);
	spin_unlock_irqrestore(&chan->vc.lock, flags);

	return 0;
}