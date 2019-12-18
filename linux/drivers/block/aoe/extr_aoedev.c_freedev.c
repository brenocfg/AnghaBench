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
struct aoetgt {int dummy; } ;
struct aoedev {int flags; int ntargets; int /*<<< orphan*/  lock; int /*<<< orphan*/  sysminor; int /*<<< orphan*/  bufpool; struct aoetgt** targets; int /*<<< orphan*/  blkq; int /*<<< orphan*/  tag_set; scalar_t__ gd; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int DEVFL_FREED ; 
 int DEVFL_FREEING ; 
 int DEVFL_TKILL ; 
 int /*<<< orphan*/  aoedisk_rm_debugfs (struct aoedev*) ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_gendisk (scalar_t__) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freetgt (struct aoedev*,struct aoetgt*) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minor_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_disk (scalar_t__) ; 
 int /*<<< orphan*/  skbpoolfree (struct aoedev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
freedev(struct aoedev *d)
{
	struct aoetgt **t, **e;
	int freeing = 0;
	unsigned long flags;

	spin_lock_irqsave(&d->lock, flags);
	if (d->flags & DEVFL_TKILL
	&& !(d->flags & DEVFL_FREEING)) {
		d->flags |= DEVFL_FREEING;
		freeing = 1;
	}
	spin_unlock_irqrestore(&d->lock, flags);
	if (!freeing)
		return;

	del_timer_sync(&d->timer);
	if (d->gd) {
		aoedisk_rm_debugfs(d);
		del_gendisk(d->gd);
		put_disk(d->gd);
		blk_mq_free_tag_set(&d->tag_set);
		blk_cleanup_queue(d->blkq);
	}
	t = d->targets;
	e = t + d->ntargets;
	for (; t < e && *t; t++)
		freetgt(d, *t);

	mempool_destroy(d->bufpool);
	skbpoolfree(d);
	minor_free(d->sysminor);

	spin_lock_irqsave(&d->lock, flags);
	d->flags |= DEVFL_FREED;
	spin_unlock_irqrestore(&d->lock, flags);
}