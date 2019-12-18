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
typedef  int /*<<< orphan*/  ulong ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct sk_buff {scalar_t__ data; } ;
struct frame {int flags; TYPE_1__* t; } ;
struct aoedev {int /*<<< orphan*/  lock; } ;
struct aoe_hdr {int minor; int /*<<< orphan*/  tag; int /*<<< orphan*/  major; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
typedef  int /*<<< orphan*/  ebuf ;
struct TYPE_2__ {int /*<<< orphan*/  nout_probes; int /*<<< orphan*/  nout; } ;

/* Variables and functions */
 int FFL_PROBE ; 
 int /*<<< orphan*/  aoechr_error (char*) ; 
 int /*<<< orphan*/  aoecmd_work (struct aoedev*) ; 
 struct aoedev* aoedev_by_aoeaddr (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aoedev_put (struct aoedev*) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calc_rttavg (struct aoedev*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_unaligned (int /*<<< orphan*/ *) ; 
 int get_unaligned_be16 (int /*<<< orphan*/ *) ; 
 int get_unaligned_be32 (int /*<<< orphan*/ *) ; 
 struct frame* getframe (struct aoedev*,int /*<<< orphan*/ ) ; 
 struct frame* getframe_deferred (struct aoedev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  ktcomplete (struct frame*,struct sk_buff*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsince (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsince_hr (struct frame*) ; 

struct sk_buff *
aoecmd_ata_rsp(struct sk_buff *skb)
{
	struct aoedev *d;
	struct aoe_hdr *h;
	struct frame *f;
	u32 n;
	ulong flags;
	char ebuf[128];
	u16 aoemajor;

	h = (struct aoe_hdr *) skb->data;
	aoemajor = be16_to_cpu(get_unaligned(&h->major));
	d = aoedev_by_aoeaddr(aoemajor, h->minor, 0);
	if (d == NULL) {
		snprintf(ebuf, sizeof ebuf, "aoecmd_ata_rsp: ata response "
			"for unknown device %d.%d\n",
			aoemajor, h->minor);
		aoechr_error(ebuf);
		return skb;
	}

	spin_lock_irqsave(&d->lock, flags);

	n = be32_to_cpu(get_unaligned(&h->tag));
	f = getframe(d, n);
	if (f) {
		calc_rttavg(d, f->t, tsince_hr(f));
		f->t->nout--;
		if (f->flags & FFL_PROBE)
			f->t->nout_probes--;
	} else {
		f = getframe_deferred(d, n);
		if (f) {
			calc_rttavg(d, NULL, tsince_hr(f));
		} else {
			calc_rttavg(d, NULL, tsince(n));
			spin_unlock_irqrestore(&d->lock, flags);
			aoedev_put(d);
			snprintf(ebuf, sizeof(ebuf),
				 "%15s e%d.%d    tag=%08x@%08lx s=%pm d=%pm\n",
				 "unexpected rsp",
				 get_unaligned_be16(&h->major),
				 h->minor,
				 get_unaligned_be32(&h->tag),
				 jiffies,
				 h->src,
				 h->dst);
			aoechr_error(ebuf);
			return skb;
		}
	}
	aoecmd_work(d);

	spin_unlock_irqrestore(&d->lock, flags);

	ktcomplete(f, skb);

	/*
	 * Note here that we do not perform an aoedev_put, as we are
	 * leaving this reference for the ktio to release.
	 */
	return NULL;
}