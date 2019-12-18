#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scatterlist {int dummy; } ;
struct hisi_zip_req_q {int size; int /*<<< orphan*/  req_lock; int /*<<< orphan*/  req_bitmap; struct hisi_zip_req* q; } ;
struct hisi_zip_req {int req_id; size_t slen; size_t dlen; struct scatterlist* dst; struct scatterlist* src; struct acomp_req* req; } ;
struct hisi_zip_qp_ctx {TYPE_3__* qp; struct hisi_zip_req_q req_q; } ;
struct acomp_req {size_t dlen; size_t slen; struct scatterlist* dst; struct scatterlist* src; } ;
struct TYPE_6__ {TYPE_2__* qm; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 struct hisi_zip_req* ERR_PTR (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int get_sg_skip_bytes (struct scatterlist*,size_t,size_t,struct scatterlist**) ; 
 int /*<<< orphan*/  kfree (struct scatterlist*) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct hisi_zip_req *hisi_zip_create_req(struct acomp_req *req,
						struct hisi_zip_qp_ctx *qp_ctx,
						size_t head_size, bool is_comp)
{
	struct hisi_zip_req_q *req_q = &qp_ctx->req_q;
	struct hisi_zip_req *q = req_q->q;
	struct hisi_zip_req *req_cache;
	struct scatterlist *out[2];
	struct scatterlist *sgl;
	size_t len;
	int ret, req_id;

	/*
	 * remove/add zlib/gzip head, as hardware operations do not include
	 * comp head. so split req->src to get sgl without heads in acomp, or
	 * add comp head to req->dst ahead of that hardware output compressed
	 * data in sgl splited from req->dst without comp head.
	 */
	if (is_comp) {
		sgl = req->dst;
		len = req->dlen - head_size;
	} else {
		sgl = req->src;
		len = req->slen - head_size;
	}

	ret = get_sg_skip_bytes(sgl, head_size, len, out);
	if (ret)
		return ERR_PTR(ret);

	/* sgl for comp head is useless, so free it now */
	kfree(out[0]);

	write_lock(&req_q->req_lock);

	req_id = find_first_zero_bit(req_q->req_bitmap, req_q->size);
	if (req_id >= req_q->size) {
		write_unlock(&req_q->req_lock);
		dev_dbg(&qp_ctx->qp->qm->pdev->dev, "req cache is full!\n");
		kfree(out[1]);
		return ERR_PTR(-EBUSY);
	}
	set_bit(req_id, req_q->req_bitmap);

	req_cache = q + req_id;
	req_cache->req_id = req_id;
	req_cache->req = req;
	if (is_comp) {
		req_cache->src = req->src;
		req_cache->dst = out[1];
		req_cache->slen = req->slen;
		req_cache->dlen = req->dlen - head_size;
	} else {
		req_cache->src = out[1];
		req_cache->dst = req->dst;
		req_cache->slen = req->slen - head_size;
		req_cache->dlen = req->dlen;
	}

	write_unlock(&req_q->req_lock);

	return req_cache;
}