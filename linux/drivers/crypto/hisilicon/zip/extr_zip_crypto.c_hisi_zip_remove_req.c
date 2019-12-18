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
struct hisi_zip_req_q {int /*<<< orphan*/  req_lock; int /*<<< orphan*/  req_bitmap; } ;
struct hisi_zip_req {int /*<<< orphan*/  req_id; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct hisi_zip_qp_ctx {TYPE_1__* qp; struct hisi_zip_req_q req_q; } ;
struct TYPE_2__ {scalar_t__ alg_type; } ;

/* Variables and functions */
 scalar_t__ HZIP_ALG_TYPE_COMP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct hisi_zip_req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hisi_zip_remove_req(struct hisi_zip_qp_ctx *qp_ctx,
				struct hisi_zip_req *req)
{
	struct hisi_zip_req_q *req_q = &qp_ctx->req_q;

	if (qp_ctx->qp->alg_type == HZIP_ALG_TYPE_COMP)
		kfree(req->dst);
	else
		kfree(req->src);

	write_lock(&req_q->req_lock);
	clear_bit(req->req_id, req_q->req_bitmap);
	memset(req, 0, sizeof(struct hisi_zip_req));
	write_unlock(&req_q->req_lock);
}