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
struct hisi_zip_ctx {TYPE_2__* qp_ctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  req_bitmap; int /*<<< orphan*/  q; } ;
struct TYPE_4__ {TYPE_1__ req_q; } ;

/* Variables and functions */
 int HZIP_CTX_Q_NUM ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hisi_zip_release_req_q(struct hisi_zip_ctx *ctx)
{
	int i;

	for (i = 0; i < HZIP_CTX_Q_NUM; i++) {
		kfree(ctx->qp_ctx[i].req_q.q);
		kfree(ctx->qp_ctx[i].req_q.req_bitmap);
	}
}