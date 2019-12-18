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
typedef  int /*<<< orphan*/  u16 ;
struct ext_int_info {int /*<<< orphan*/  entry; int /*<<< orphan*/  handler; int /*<<< orphan*/  code; } ;
typedef  int /*<<< orphan*/  ext_int_handler_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int ext_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ext_int_hash ; 
 int /*<<< orphan*/  ext_int_hash_lock ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ext_int_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int register_external_irq(u16 code, ext_int_handler_t handler)
{
	struct ext_int_info *p;
	unsigned long flags;
	int index;

	p = kmalloc(sizeof(*p), GFP_ATOMIC);
	if (!p)
		return -ENOMEM;
	p->code = code;
	p->handler = handler;
	index = ext_hash(code);

	spin_lock_irqsave(&ext_int_hash_lock, flags);
	hlist_add_head_rcu(&p->entry, &ext_int_hash[index]);
	spin_unlock_irqrestore(&ext_int_hash_lock, flags);
	return 0;
}