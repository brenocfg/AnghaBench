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
struct sk_buff {int dummy; } ;
struct eni_tx {int /*<<< orphan*/  backlog; scalar_t__ send; } ;
struct atm_dev {int dummy; } ;
typedef  enum enq_res { ____Placeholder_enq_res } enq_res ;
struct TYPE_2__ {struct eni_tx* tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 TYPE_1__* ENI_DEV (struct atm_dev*) ; 
 int NR_CHAN ; 
 int do_tx (struct sk_buff*) ; 
 int enq_jam ; 
 int enq_ok ; 
 int /*<<< orphan*/  requeued ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void poll_tx(struct atm_dev *dev)
{
	struct eni_tx *tx;
	struct sk_buff *skb;
	enum enq_res res;
	int i;

	DPRINTK(">poll_tx\n");
	for (i = NR_CHAN-1; i >= 0; i--) {
		tx = &ENI_DEV(dev)->tx[i];
		if (tx->send)
			while ((skb = skb_dequeue(&tx->backlog))) {
				res = do_tx(skb);
				if (res == enq_ok) continue;
				DPRINTK("re-queuing TX PDU\n");
				skb_queue_head(&tx->backlog,skb);
				requeued++;
				if (res == enq_jam) return;
				break;
			}
	}
}