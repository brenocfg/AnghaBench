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
typedef  int /*<<< orphan*/  u32 ;
struct atmel_aes_gcm_ctx {scalar_t__ textlen; int /*<<< orphan*/ * j0; } ;
struct atmel_aes_dev {scalar_t__ datalen; scalar_t__ buflen; scalar_t__ buf; int /*<<< orphan*/ * data; int /*<<< orphan*/  areq; int /*<<< orphan*/  ctx; } ;
struct aead_request {scalar_t__ assoclen; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_AADLENR ; 
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  AES_CLENR ; 
 int /*<<< orphan*/  AES_IVR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 struct aead_request* aead_request_cast (int /*<<< orphan*/ ) ; 
 int atmel_aes_complete (struct atmel_aes_dev*,int /*<<< orphan*/ ) ; 
 struct atmel_aes_gcm_ctx* atmel_aes_gcm_ctx_cast (int /*<<< orphan*/ ) ; 
 int atmel_aes_gcm_data (struct atmel_aes_dev*) ; 
 size_t atmel_aes_padlen (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_aes_write (struct atmel_aes_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  atmel_aes_write_block (struct atmel_aes_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sg_nents (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int atmel_aes_gcm_length(struct atmel_aes_dev *dd)
{
	struct atmel_aes_gcm_ctx *ctx = atmel_aes_gcm_ctx_cast(dd->ctx);
	struct aead_request *req = aead_request_cast(dd->areq);
	u32 j0_lsw, *j0 = ctx->j0;
	size_t padlen;

	/* Write incr32(J0) into IV. */
	j0_lsw = j0[3];
	j0[3] = cpu_to_be32(be32_to_cpu(j0[3]) + 1);
	atmel_aes_write_block(dd, AES_IVR(0), j0);
	j0[3] = j0_lsw;

	/* Set aad and text lengths. */
	atmel_aes_write(dd, AES_AADLENR, req->assoclen);
	atmel_aes_write(dd, AES_CLENR, ctx->textlen);

	/* Check whether AAD are present. */
	if (unlikely(req->assoclen == 0)) {
		dd->datalen = 0;
		return atmel_aes_gcm_data(dd);
	}

	/* Copy assoc data and add padding. */
	padlen = atmel_aes_padlen(req->assoclen, AES_BLOCK_SIZE);
	if (unlikely(req->assoclen + padlen > dd->buflen))
		return atmel_aes_complete(dd, -EINVAL);
	sg_copy_to_buffer(req->src, sg_nents(req->src), dd->buf, req->assoclen);

	/* Write assoc data into the Input Data register. */
	dd->data = (u32 *)dd->buf;
	dd->datalen = req->assoclen + padlen;
	return atmel_aes_gcm_data(dd);
}