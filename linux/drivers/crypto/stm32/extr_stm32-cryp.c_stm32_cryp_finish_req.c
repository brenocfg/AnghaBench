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
struct stm32_cryp {TYPE_1__* ctx; int /*<<< orphan*/  req; int /*<<< orphan*/  engine; int /*<<< orphan*/  areq; int /*<<< orphan*/  dev; int /*<<< orphan*/  hw_blocksize; int /*<<< orphan*/  total_out_save; int /*<<< orphan*/  total_in_save; int /*<<< orphan*/  out_sg_save; int /*<<< orphan*/  out_sgl; int /*<<< orphan*/  in_sgl; scalar_t__ sgs_copied; } ;
struct TYPE_2__ {int /*<<< orphan*/  keylen; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_finalize_ablkcipher_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  crypto_finalize_aead_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 int get_order (int) ; 
 scalar_t__ is_ccm (struct stm32_cryp*) ; 
 scalar_t__ is_gcm (struct stm32_cryp*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_copy_buf (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* sg_virt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stm32_cryp_get_iv (struct stm32_cryp*) ; 
 int stm32_cryp_read_auth_tag (struct stm32_cryp*) ; 

__attribute__((used)) static void stm32_cryp_finish_req(struct stm32_cryp *cryp, int err)
{
	if (!err && (is_gcm(cryp) || is_ccm(cryp)))
		/* Phase 4 : output tag */
		err = stm32_cryp_read_auth_tag(cryp);

	if (!err && (!(is_gcm(cryp) || is_ccm(cryp))))
		stm32_cryp_get_iv(cryp);

	if (cryp->sgs_copied) {
		void *buf_in, *buf_out;
		int pages, len;

		buf_in = sg_virt(&cryp->in_sgl);
		buf_out = sg_virt(&cryp->out_sgl);

		sg_copy_buf(buf_out, cryp->out_sg_save, 0,
			    cryp->total_out_save, 1);

		len = ALIGN(cryp->total_in_save, cryp->hw_blocksize);
		pages = len ? get_order(len) : 1;
		free_pages((unsigned long)buf_in, pages);

		len = ALIGN(cryp->total_out_save, cryp->hw_blocksize);
		pages = len ? get_order(len) : 1;
		free_pages((unsigned long)buf_out, pages);
	}

	pm_runtime_mark_last_busy(cryp->dev);
	pm_runtime_put_autosuspend(cryp->dev);

	if (is_gcm(cryp) || is_ccm(cryp))
		crypto_finalize_aead_request(cryp->engine, cryp->areq, err);
	else
		crypto_finalize_ablkcipher_request(cryp->engine, cryp->req,
						   err);

	memset(cryp->ctx->key, 0, cryp->ctx->keylen);
}