#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hisi_zip_qp_ctx {int /*<<< orphan*/  qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  hisi_qm_release_qp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_qm_stop_qp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hisi_zip_release_qp(struct hisi_zip_qp_ctx *ctx)
{
	hisi_qm_stop_qp(ctx->qp);
	hisi_qm_release_qp(ctx->qp);
}