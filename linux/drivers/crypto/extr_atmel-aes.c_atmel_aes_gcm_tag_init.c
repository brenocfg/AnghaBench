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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct atmel_aes_gcm_ctx {int textlen; int /*<<< orphan*/  ghash; } ;
struct atmel_aes_dev {int flags; int (* resume ) (struct atmel_aes_dev*) ;int /*<<< orphan*/ * buf; int /*<<< orphan*/  areq; int /*<<< orphan*/  ctx; } ;
struct aead_request {int assoclen; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int AES_FLAGS_GTAGEN ; 
 int /*<<< orphan*/  AES_GHASHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AES_IER ; 
 int AES_INT_TAGRDY ; 
 int /*<<< orphan*/  AES_ISR ; 
 int EINPROGRESS ; 
 struct aead_request* aead_request_cast (int /*<<< orphan*/ ) ; 
 struct atmel_aes_gcm_ctx* atmel_aes_gcm_ctx_cast (int /*<<< orphan*/ ) ; 
 int atmel_aes_gcm_finalize (struct atmel_aes_dev*) ; 
 int atmel_aes_gcm_ghash (struct atmel_aes_dev*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_aes_gcm_tag ; 
 int atmel_aes_read (struct atmel_aes_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_aes_read_block (struct atmel_aes_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_aes_write (struct atmel_aes_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int atmel_aes_gcm_tag_init(struct atmel_aes_dev *dd)
{
	struct atmel_aes_gcm_ctx *ctx = atmel_aes_gcm_ctx_cast(dd->ctx);
	struct aead_request *req = aead_request_cast(dd->areq);
	u64 *data = dd->buf;

	if (likely(dd->flags & AES_FLAGS_GTAGEN)) {
		if (!(atmel_aes_read(dd, AES_ISR) & AES_INT_TAGRDY)) {
			dd->resume = atmel_aes_gcm_tag_init;
			atmel_aes_write(dd, AES_IER, AES_INT_TAGRDY);
			return -EINPROGRESS;
		}

		return atmel_aes_gcm_finalize(dd);
	}

	/* Read the GCM Intermediate Hash Word Registers. */
	atmel_aes_read_block(dd, AES_GHASHR(0), ctx->ghash);

	data[0] = cpu_to_be64(req->assoclen * 8);
	data[1] = cpu_to_be64(ctx->textlen * 8);

	return atmel_aes_gcm_ghash(dd, (const u32 *)data, AES_BLOCK_SIZE,
				   ctx->ghash, ctx->ghash, atmel_aes_gcm_tag);
}