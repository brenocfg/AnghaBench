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
struct kvmppc_xive_src_block {int id; TYPE_1__* irq_state; } ;
struct kvmppc_xive {int max_sbid; struct kvmppc_xive_src_block** src_blocks; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int number; void* act_priority; void* saved_priority; void* guest_priority; scalar_t__ eisn; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int KVMPPC_XICS_ICS_SHIFT ; 
 int KVMPPC_XICS_IRQ_PER_ICS ; 
 void* MASKED ; 
 struct kvmppc_xive_src_block* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 

struct kvmppc_xive_src_block *kvmppc_xive_create_src_block(
	struct kvmppc_xive *xive, int irq)
{
	struct kvmppc_xive_src_block *sb;
	int i, bid;

	bid = irq >> KVMPPC_XICS_ICS_SHIFT;

	mutex_lock(&xive->lock);

	/* block already exists - somebody else got here first */
	if (xive->src_blocks[bid])
		goto out;

	/* Create the ICS */
	sb = kzalloc(sizeof(*sb), GFP_KERNEL);
	if (!sb)
		goto out;

	sb->id = bid;

	for (i = 0; i < KVMPPC_XICS_IRQ_PER_ICS; i++) {
		sb->irq_state[i].number = (bid << KVMPPC_XICS_ICS_SHIFT) | i;
		sb->irq_state[i].eisn = 0;
		sb->irq_state[i].guest_priority = MASKED;
		sb->irq_state[i].saved_priority = MASKED;
		sb->irq_state[i].act_priority = MASKED;
	}
	smp_wmb();
	xive->src_blocks[bid] = sb;

	if (bid > xive->max_sbid)
		xive->max_sbid = bid;

out:
	mutex_unlock(&xive->lock);
	return xive->src_blocks[bid];
}