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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {unsigned int dst_len; } ;
struct pkcs1pad_request {int /*<<< orphan*/  in_buf; TYPE_1__ child_req; } ;
struct pkcs1pad_ctx {unsigned int key_size; } ;
struct crypto_akcipher {int dummy; } ;
struct akcipher_request {unsigned int dst_len; int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct pkcs1pad_request* akcipher_request_ctx (struct akcipher_request*) ; 
 struct pkcs1pad_ctx* akcipher_tfm_ctx (struct crypto_akcipher*) ; 
 struct crypto_akcipher* crypto_akcipher_reqtfm (struct akcipher_request*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  sg_copy_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  sg_copy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  sg_nents_for_len (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int pkcs1pad_encrypt_sign_complete(struct akcipher_request *req, int err)
{
	struct crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	struct pkcs1pad_ctx *ctx = akcipher_tfm_ctx(tfm);
	struct pkcs1pad_request *req_ctx = akcipher_request_ctx(req);
	unsigned int pad_len;
	unsigned int len;
	u8 *out_buf;

	if (err)
		goto out;

	len = req_ctx->child_req.dst_len;
	pad_len = ctx->key_size - len;

	/* Four billion to one */
	if (likely(!pad_len))
		goto out;

	out_buf = kzalloc(ctx->key_size, GFP_KERNEL);
	err = -ENOMEM;
	if (!out_buf)
		goto out;

	sg_copy_to_buffer(req->dst, sg_nents_for_len(req->dst, len),
			  out_buf + pad_len, len);
	sg_copy_from_buffer(req->dst,
			    sg_nents_for_len(req->dst, ctx->key_size),
			    out_buf, ctx->key_size);
	kzfree(out_buf);

out:
	req->dst_len = ctx->key_size;

	kfree(req_ctx->in_buf);

	return err;
}