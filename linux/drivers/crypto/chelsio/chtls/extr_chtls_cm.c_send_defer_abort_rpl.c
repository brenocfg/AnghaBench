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
struct cpl_abort_rpl {int dummy; } ;
struct cpl_abort_req_rss {int status; } ;
struct chtls_dev {TYPE_1__* lldi; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ports; } ;

/* Variables and functions */
 int CPL_ABORT_NO_RST ; 
 int /*<<< orphan*/  CPL_PRIORITY_DATA ; 
 int /*<<< orphan*/  GET_TID (struct cpl_abort_req_rss*) ; 
 int GFP_KERNEL ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,int) ; 
 struct sk_buff* alloc_skb (int,int) ; 
 struct cpl_abort_req_rss* cplhdr (struct sk_buff*) ; 
 int /*<<< orphan*/  cxgb4_ofld_send (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  set_abort_rpl_wr (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_wr_txq (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void send_defer_abort_rpl(struct chtls_dev *cdev, struct sk_buff *skb)
{
	struct cpl_abort_req_rss *req = cplhdr(skb);
	struct sk_buff *reply_skb;

	reply_skb = alloc_skb(sizeof(struct cpl_abort_rpl),
			      GFP_KERNEL | __GFP_NOFAIL);
	__skb_put(reply_skb, sizeof(struct cpl_abort_rpl));
	set_abort_rpl_wr(reply_skb, GET_TID(req),
			 (req->status & CPL_ABORT_NO_RST));
	set_wr_txq(reply_skb, CPL_PRIORITY_DATA, req->status >> 1);
	cxgb4_ofld_send(cdev->lldi->ports[0], reply_skb);
	kfree_skb(skb);
}