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
struct hisi_zip_ctx {int /*<<< orphan*/ * qp_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  hisi_zip_release_qp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hisi_zip_ctx_exit(struct hisi_zip_ctx *hisi_zip_ctx)
{
	int i;

	for (i = 1; i >= 0; i--)
		hisi_zip_release_qp(&hisi_zip_ctx->qp_ctx[i]);
}