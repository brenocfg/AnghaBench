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
typedef  int u8 ;
struct rsa_asn1_template {scalar_t__ size; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {unsigned int dst_len; } ;
struct pkcs1pad_request {int* out_buf; TYPE_1__ child_req; } ;
struct pkcs1pad_inst_ctx {struct rsa_asn1_template* digest_info; } ;
struct pkcs1pad_ctx {int key_size; } ;
struct crypto_akcipher {int dummy; } ;
struct akcipher_request {unsigned int dst_len; scalar_t__ src_len; int /*<<< orphan*/  src; } ;
struct akcipher_instance {int dummy; } ;

/* Variables and functions */
 int EBADMSG ; 
 int EINVAL ; 
 int EKEYREJECTED ; 
 struct akcipher_instance* akcipher_alg_instance (struct crypto_akcipher*) ; 
 struct pkcs1pad_inst_ctx* akcipher_instance_ctx (struct akcipher_instance*) ; 
 struct pkcs1pad_request* akcipher_request_ctx (struct akcipher_request*) ; 
 struct pkcs1pad_ctx* akcipher_tfm_ctx (struct crypto_akcipher*) ; 
 struct crypto_akcipher* crypto_akcipher_reqtfm (struct akcipher_request*) ; 
 scalar_t__ crypto_memneq (int*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kzfree (int*) ; 
 scalar_t__ memcmp (int*,int*,unsigned int) ; 
 int /*<<< orphan*/  sg_nents_for_len (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sg_pcopy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,unsigned int,int) ; 

__attribute__((used)) static int pkcs1pad_verify_complete(struct akcipher_request *req, int err)
{
	struct crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	struct pkcs1pad_ctx *ctx = akcipher_tfm_ctx(tfm);
	struct pkcs1pad_request *req_ctx = akcipher_request_ctx(req);
	struct akcipher_instance *inst = akcipher_alg_instance(tfm);
	struct pkcs1pad_inst_ctx *ictx = akcipher_instance_ctx(inst);
	const struct rsa_asn1_template *digest_info = ictx->digest_info;
	unsigned int dst_len;
	unsigned int pos;
	u8 *out_buf;

	if (err)
		goto done;

	err = -EINVAL;
	dst_len = req_ctx->child_req.dst_len;
	if (dst_len < ctx->key_size - 1)
		goto done;

	out_buf = req_ctx->out_buf;
	if (dst_len == ctx->key_size) {
		if (out_buf[0] != 0x00)
			/* Decrypted value had no leading 0 byte */
			goto done;

		dst_len--;
		out_buf++;
	}

	err = -EBADMSG;
	if (out_buf[0] != 0x01)
		goto done;

	for (pos = 1; pos < dst_len; pos++)
		if (out_buf[pos] != 0xff)
			break;

	if (pos < 9 || pos == dst_len || out_buf[pos] != 0x00)
		goto done;
	pos++;

	if (digest_info) {
		if (crypto_memneq(out_buf + pos, digest_info->data,
				  digest_info->size))
			goto done;

		pos += digest_info->size;
	}

	err = 0;

	if (req->dst_len != dst_len - pos) {
		err = -EKEYREJECTED;
		req->dst_len = dst_len - pos;
		goto done;
	}
	/* Extract appended digest. */
	sg_pcopy_to_buffer(req->src,
			   sg_nents_for_len(req->src,
					    req->src_len + req->dst_len),
			   req_ctx->out_buf + ctx->key_size,
			   req->dst_len, ctx->key_size);
	/* Do the actual verification step. */
	if (memcmp(req_ctx->out_buf + ctx->key_size, out_buf + pos,
		   req->dst_len) != 0)
		err = -EKEYREJECTED;
done:
	kzfree(req_ctx->out_buf);

	return err;
}