#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* ulong ;
struct TYPE_3__ {scalar_t__ expires; } ;
struct aoedev {void* aoemajor; int aoeminor; int flags; int ref; int ntargets; struct aoedev* next; int /*<<< orphan*/  rttdev; int /*<<< orphan*/  rttavg; void* sysminor; int /*<<< orphan*/  rexmitq; int /*<<< orphan*/ * factive; void* targets; void* tgt; int /*<<< orphan*/ * bufpool; TYPE_1__ timer; int /*<<< orphan*/  skbpool; int /*<<< orphan*/  rq_list; int /*<<< orphan*/  lock; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int DEVFL_TKILL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NFACTIVE ; 
 int NTARGETS ; 
 int /*<<< orphan*/  RTTAVG_INIT ; 
 int /*<<< orphan*/  RTTDEV_INIT ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  aoecmd_sleepwork ; 
 struct aoedev* devlist ; 
 int /*<<< orphan*/  devlist_lock ; 
 int /*<<< orphan*/  dummy_timer ; 
 scalar_t__ jiffies ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct aoedev*) ; 
 scalar_t__ minor_get (void**,void*,int) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  timer_setup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct aoedev *
aoedev_by_aoeaddr(ulong maj, int min, int do_alloc)
{
	struct aoedev *d;
	int i;
	ulong flags;
	ulong sysminor = 0;

	spin_lock_irqsave(&devlist_lock, flags);

	for (d=devlist; d; d=d->next)
		if (d->aoemajor == maj && d->aoeminor == min) {
			spin_lock(&d->lock);
			if (d->flags & DEVFL_TKILL) {
				spin_unlock(&d->lock);
				d = NULL;
				goto out;
			}
			d->ref++;
			spin_unlock(&d->lock);
			break;
		}
	if (d || !do_alloc || minor_get(&sysminor, maj, min) < 0)
		goto out;
	d = kcalloc(1, sizeof *d, GFP_ATOMIC);
	if (!d)
		goto out;
	d->targets = kcalloc(NTARGETS, sizeof(*d->targets), GFP_ATOMIC);
	if (!d->targets) {
		kfree(d);
		d = NULL;
		goto out;
	}
	d->ntargets = NTARGETS;
	INIT_WORK(&d->work, aoecmd_sleepwork);
	spin_lock_init(&d->lock);
	INIT_LIST_HEAD(&d->rq_list);
	skb_queue_head_init(&d->skbpool);
	timer_setup(&d->timer, dummy_timer, 0);
	d->timer.expires = jiffies + HZ;
	add_timer(&d->timer);
	d->bufpool = NULL;	/* defer to aoeblk_gdalloc */
	d->tgt = d->targets;
	d->ref = 1;
	for (i = 0; i < NFACTIVE; i++)
		INIT_LIST_HEAD(&d->factive[i]);
	INIT_LIST_HEAD(&d->rexmitq);
	d->sysminor = sysminor;
	d->aoemajor = maj;
	d->aoeminor = min;
	d->rttavg = RTTAVG_INIT;
	d->rttdev = RTTDEV_INIT;
	d->next = devlist;
	devlist = d;
 out:
	spin_unlock_irqrestore(&devlist_lock, flags);
	return d;
}