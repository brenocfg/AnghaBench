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
struct hisi_zip_req_q {void* req_bitmap; void* q; int /*<<< orphan*/  size; int /*<<< orphan*/  req_lock; } ;
struct hisi_zip_req {int dummy; } ;
struct hisi_zip_ctx {TYPE_1__* qp_ctx; } ;
struct TYPE_2__ {struct hisi_zip_req_q req_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZIP_CTX_Q_NUM ; 
 int /*<<< orphan*/  QM_Q_DEPTH ; 
 size_t QPC_COMP ; 
 size_t QPC_DECOMP ; 
 void* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hisi_zip_create_req_q(struct hisi_zip_ctx *ctx)
{
	struct hisi_zip_req_q *req_q;
	int i, ret;

	for (i = 0; i < HZIP_CTX_Q_NUM; i++) {
		req_q = &ctx->qp_ctx[i].req_q;
		req_q->size = QM_Q_DEPTH;

		req_q->req_bitmap = kcalloc(BITS_TO_LONGS(req_q->size),
					    sizeof(long), GFP_KERNEL);
		if (!req_q->req_bitmap) {
			ret = -ENOMEM;
			if (i == 0)
				return ret;

			goto err_free_loop0;
		}
		rwlock_init(&req_q->req_lock);

		req_q->q = kcalloc(req_q->size, sizeof(struct hisi_zip_req),
				   GFP_KERNEL);
		if (!req_q->q) {
			ret = -ENOMEM;
			if (i == 0)
				goto err_free_bitmap;
			else
				goto err_free_loop1;
		}
	}

	return 0;

err_free_loop1:
	kfree(ctx->qp_ctx[QPC_DECOMP].req_q.req_bitmap);
err_free_loop0:
	kfree(ctx->qp_ctx[QPC_COMP].req_q.q);
err_free_bitmap:
	kfree(ctx->qp_ctx[QPC_COMP].req_q.req_bitmap);
	return ret;
}