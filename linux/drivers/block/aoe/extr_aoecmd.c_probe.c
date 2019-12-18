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
struct sk_buff_head {int dummy; } ;
struct sk_buff {size_t len; size_t data_len; size_t truesize; } ;
struct TYPE_2__ {size_t bi_size; } ;
struct frame {int /*<<< orphan*/  sent; struct sk_buff* skb; TYPE_1__ iter; int /*<<< orphan*/  flags; } ;
struct aoetgt {struct aoedev* d; int /*<<< orphan*/  addr; } ;
struct aoedev {size_t maxbcnt; int /*<<< orphan*/  aoeminor; scalar_t__ aoemajor; } ;

/* Variables and functions */
 size_t DEFAULTBCNT ; 
 int /*<<< orphan*/  FFL_PROBE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  aoenet_xmit (struct sk_buff_head*) ; 
 int /*<<< orphan*/  ata_rw_frameinit (struct frame*) ; 
 int /*<<< orphan*/  empty_page ; 
 int /*<<< orphan*/  ifrotate (struct aoetgt*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 struct frame* newtframe (struct aoedev*,struct aoetgt*) ; 
 int /*<<< orphan*/  pr_err (char*,char*,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ,char*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_fill_page_desc (struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
probe(struct aoetgt *t)
{
	struct aoedev *d;
	struct frame *f;
	struct sk_buff *skb;
	struct sk_buff_head queue;
	size_t n, m;
	int frag;

	d = t->d;
	f = newtframe(d, t);
	if (!f) {
		pr_err("%s %pm for e%ld.%d: %s\n",
			"aoe: cannot probe remote address",
			t->addr,
			(long) d->aoemajor, d->aoeminor,
			"no frame available");
		return;
	}
	f->flags |= FFL_PROBE;
	ifrotate(t);
	f->iter.bi_size = t->d->maxbcnt ? t->d->maxbcnt : DEFAULTBCNT;
	ata_rw_frameinit(f);
	skb = f->skb;
	for (frag = 0, n = f->iter.bi_size; n > 0; ++frag, n -= m) {
		if (n < PAGE_SIZE)
			m = n;
		else
			m = PAGE_SIZE;
		skb_fill_page_desc(skb, frag, empty_page, 0, m);
	}
	skb->len += f->iter.bi_size;
	skb->data_len = f->iter.bi_size;
	skb->truesize += f->iter.bi_size;

	skb = skb_clone(f->skb, GFP_ATOMIC);
	if (skb) {
		f->sent = ktime_get();
		__skb_queue_head_init(&queue);
		__skb_queue_tail(&queue, skb);
		aoenet_xmit(&queue);
	}
}