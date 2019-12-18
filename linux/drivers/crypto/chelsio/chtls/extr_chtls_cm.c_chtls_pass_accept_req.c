#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct listen_ctx {struct sock* lsk; } ;
struct cpl_pass_accept_req {int /*<<< orphan*/  tos_stid; } ;
struct chtls_dev {TYPE_1__* tids; } ;
struct TYPE_4__ {struct chtls_dev* cdev; } ;
struct TYPE_3__ {unsigned int ntids; } ;

/* Variables and functions */
 TYPE_2__* BLOG_SKB_CB (struct sk_buff*) ; 
 unsigned int GET_TID (struct cpl_pass_accept_req*) ; 
 unsigned int PASS_OPEN_TID_G (int /*<<< orphan*/ ) ; 
 int RSS_HDR ; 
 int /*<<< orphan*/  chtls_pass_accept_request ; 
 struct cpl_pass_accept_req* cplhdr (struct sk_buff*) ; 
 void* lookup_stid (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int) ; 
 int /*<<< orphan*/  process_cpl_msg (int /*<<< orphan*/ ,struct sock*,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int chtls_pass_accept_req(struct chtls_dev *cdev, struct sk_buff *skb)
{
	struct cpl_pass_accept_req *req = cplhdr(skb) + RSS_HDR;
	struct listen_ctx *ctx;
	unsigned int stid;
	unsigned int tid;
	struct sock *lsk;
	void *data;

	stid = PASS_OPEN_TID_G(ntohl(req->tos_stid));
	tid = GET_TID(req);

	data = lookup_stid(cdev->tids, stid);
	if (!data)
		return 1;

	ctx = (struct listen_ctx *)data;
	lsk = ctx->lsk;

	if (unlikely(tid >= cdev->tids->ntids)) {
		pr_info("passive open TID %u too large\n", tid);
		return 1;
	}

	BLOG_SKB_CB(skb)->cdev = cdev;
	process_cpl_msg(chtls_pass_accept_request, lsk, skb);
	return 0;
}