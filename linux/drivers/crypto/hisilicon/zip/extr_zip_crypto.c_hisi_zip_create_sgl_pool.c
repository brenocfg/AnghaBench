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
struct hisi_zip_qp_ctx {int /*<<< orphan*/  sgl_pool; TYPE_3__* qp; } ;
struct hisi_zip_ctx {struct hisi_zip_qp_ctx* qp_ctx; } ;
struct TYPE_6__ {TYPE_2__* qm; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int HZIP_CTX_Q_NUM ; 
 int QM_Q_DEPTH ; 
 size_t QPC_COMP ; 
 int hisi_acc_create_sgl_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hisi_acc_free_sgl_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hisi_zip_create_sgl_pool(struct hisi_zip_ctx *ctx)
{
	struct hisi_zip_qp_ctx *tmp;
	int i, ret;

	for (i = 0; i < HZIP_CTX_Q_NUM; i++) {
		tmp = &ctx->qp_ctx[i];
		ret = hisi_acc_create_sgl_pool(&tmp->qp->qm->pdev->dev,
					       &tmp->sgl_pool,
					       QM_Q_DEPTH << 1);
		if (ret < 0) {
			if (i == 1)
				goto err_free_sgl_pool0;
			return -ENOMEM;
		}
	}

	return 0;

err_free_sgl_pool0:
	hisi_acc_free_sgl_pool(&ctx->qp_ctx[QPC_COMP].qp->qm->pdev->dev,
			       &ctx->qp_ctx[QPC_COMP].sgl_pool);
	return -ENOMEM;
}