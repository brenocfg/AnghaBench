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
struct listen_ctx {scalar_t__ state; TYPE_1__* lsk; } ;
struct cpl_pass_open_rpl {scalar_t__ status; } ;
struct chtls_dev {int /*<<< orphan*/  tids; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk_family; } ;

/* Variables and functions */
 scalar_t__ CPL_ERR_NONE ; 
 int CPL_RET_BUF_DONE ; 
 unsigned int GET_TID (struct cpl_pass_open_rpl*) ; 
 int RSS_HDR ; 
 scalar_t__ T4_LISTEN_STARTED ; 
 scalar_t__ T4_LISTEN_START_PENDING ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct cpl_pass_open_rpl* cplhdr (struct sk_buff*) ; 
 int /*<<< orphan*/  cxgb4_free_stid (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct listen_ctx*) ; 
 scalar_t__ lookup_stid (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  sock_put (TYPE_1__*) ; 

__attribute__((used)) static int chtls_pass_open_rpl(struct chtls_dev *cdev, struct sk_buff *skb)
{
	struct cpl_pass_open_rpl *rpl = cplhdr(skb) + RSS_HDR;
	unsigned int stid = GET_TID(rpl);
	struct listen_ctx *listen_ctx;

	listen_ctx = (struct listen_ctx *)lookup_stid(cdev->tids, stid);
	if (!listen_ctx)
		return CPL_RET_BUF_DONE;

	if (listen_ctx->state == T4_LISTEN_START_PENDING) {
		listen_ctx->state = T4_LISTEN_STARTED;
		return CPL_RET_BUF_DONE;
	}

	if (rpl->status != CPL_ERR_NONE) {
		pr_info("Unexpected PASS_OPEN_RPL status %u for STID %u\n",
			rpl->status, stid);
		return CPL_RET_BUF_DONE;
	}
	cxgb4_free_stid(cdev->tids, stid, listen_ctx->lsk->sk_family);
	sock_put(listen_ctx->lsk);
	kfree(listen_ctx);
	module_put(THIS_MODULE);

	return 0;
}