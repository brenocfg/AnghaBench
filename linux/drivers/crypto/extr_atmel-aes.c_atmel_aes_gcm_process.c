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
typedef  scalar_t__ u32 ;
struct crypto_aead {int dummy; } ;
struct atmel_aes_gcm_ctx {scalar_t__ textlen; } ;
struct atmel_aes_dev {int /*<<< orphan*/  flags; int /*<<< orphan*/  areq; int /*<<< orphan*/  ctx; } ;
struct aead_request {scalar_t__ cryptlen; scalar_t__ assoclen; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_FLAGS_GTAGEN ; 
 struct aead_request* aead_request_cast (int /*<<< orphan*/ ) ; 
 struct atmel_aes_gcm_ctx* atmel_aes_gcm_ctx_cast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_aes_gcm_length ; 
 int atmel_aes_is_encrypt (struct atmel_aes_dev*) ; 
 int atmel_aes_wait_for_data_ready (struct atmel_aes_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_aes_write_ctrl (struct atmel_aes_dev*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ crypto_aead_authsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int atmel_aes_gcm_process(struct atmel_aes_dev *dd)
{
	struct atmel_aes_gcm_ctx *ctx = atmel_aes_gcm_ctx_cast(dd->ctx);
	struct aead_request *req = aead_request_cast(dd->areq);
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	bool enc = atmel_aes_is_encrypt(dd);
	u32 authsize;

	/* Compute text length. */
	authsize = crypto_aead_authsize(tfm);
	ctx->textlen = req->cryptlen - (enc ? 0 : authsize);

	/*
	 * According to tcrypt test suite, the GCM Automatic Tag Generation
	 * fails when both the message and its associated data are empty.
	 */
	if (likely(req->assoclen != 0 || ctx->textlen != 0))
		dd->flags |= AES_FLAGS_GTAGEN;

	atmel_aes_write_ctrl(dd, false, NULL);
	return atmel_aes_wait_for_data_ready(dd, atmel_aes_gcm_length);
}