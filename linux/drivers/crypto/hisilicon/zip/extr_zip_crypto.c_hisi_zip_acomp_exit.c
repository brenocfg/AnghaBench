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
struct hisi_zip_ctx {int dummy; } ;
struct crypto_acomp {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 struct hisi_zip_ctx* crypto_tfm_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hisi_zip_ctx_exit (struct hisi_zip_ctx*) ; 
 int /*<<< orphan*/  hisi_zip_release_req_q (struct hisi_zip_ctx*) ; 
 int /*<<< orphan*/  hisi_zip_release_sgl_pool (struct hisi_zip_ctx*) ; 
 int /*<<< orphan*/  hisi_zip_set_acomp_cb (struct hisi_zip_ctx*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hisi_zip_acomp_exit(struct crypto_acomp *tfm)
{
	struct hisi_zip_ctx *ctx = crypto_tfm_ctx(&tfm->base);

	hisi_zip_set_acomp_cb(ctx, NULL);
	hisi_zip_release_sgl_pool(ctx);
	hisi_zip_release_req_q(ctx);
	hisi_zip_ctx_exit(ctx);
}