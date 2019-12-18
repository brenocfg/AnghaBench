#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hisi_zip_ctx {TYPE_4__* qp_ctx; } ;
struct TYPE_8__ {int /*<<< orphan*/  sgl_pool; TYPE_3__* qp; } ;
struct TYPE_7__ {TYPE_2__* qm; } ;
struct TYPE_6__ {TYPE_1__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HZIP_CTX_Q_NUM ; 
 int /*<<< orphan*/  hisi_acc_free_sgl_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hisi_zip_release_sgl_pool(struct hisi_zip_ctx *ctx)
{
	int i;

	for (i = 0; i < HZIP_CTX_Q_NUM; i++)
		hisi_acc_free_sgl_pool(&ctx->qp_ctx[i].qp->qm->pdev->dev,
				       &ctx->qp_ctx[i].sgl_pool);
}