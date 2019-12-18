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
typedef  int u64 ;
struct crypto_aead {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  complete; int /*<<< orphan*/  flags; } ;
struct aead_request {unsigned int cryptlen; int* iv; int /*<<< orphan*/  assoclen; int /*<<< orphan*/  dst; TYPE_1__ base; int /*<<< orphan*/  src; } ;
struct aead_geniv_ctx {int* salt; int /*<<< orphan*/  sknull; int /*<<< orphan*/  child; } ;
typedef  int __be64 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SYNC_SKCIPHER_REQUEST_ON_STACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct aead_request* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  aead_request_set_ad (struct aead_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_set_callback (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_set_crypt (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int*) ; 
 int /*<<< orphan*/  aead_request_set_tfm (struct aead_request*,int /*<<< orphan*/ ) ; 
 int be64_to_cpu (int) ; 
 struct aead_geniv_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int crypto_aead_encrypt (struct aead_request*) ; 
 unsigned int crypto_aead_ivsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int crypto_skcipher_encrypt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  nreq ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_sync_tfm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int echainiv_encrypt(struct aead_request *req)
{
	struct crypto_aead *geniv = crypto_aead_reqtfm(req);
	struct aead_geniv_ctx *ctx = crypto_aead_ctx(geniv);
	struct aead_request *subreq = aead_request_ctx(req);
	__be64 nseqno;
	u64 seqno;
	u8 *info;
	unsigned int ivsize = crypto_aead_ivsize(geniv);
	int err;

	if (req->cryptlen < ivsize)
		return -EINVAL;

	aead_request_set_tfm(subreq, ctx->child);

	info = req->iv;

	if (req->src != req->dst) {
		SYNC_SKCIPHER_REQUEST_ON_STACK(nreq, ctx->sknull);

		skcipher_request_set_sync_tfm(nreq, ctx->sknull);
		skcipher_request_set_callback(nreq, req->base.flags,
					      NULL, NULL);
		skcipher_request_set_crypt(nreq, req->src, req->dst,
					   req->assoclen + req->cryptlen,
					   NULL);

		err = crypto_skcipher_encrypt(nreq);
		if (err)
			return err;
	}

	aead_request_set_callback(subreq, req->base.flags,
				  req->base.complete, req->base.data);
	aead_request_set_crypt(subreq, req->dst, req->dst,
			       req->cryptlen, info);
	aead_request_set_ad(subreq, req->assoclen);

	memcpy(&nseqno, info + ivsize - 8, 8);
	seqno = be64_to_cpu(nseqno);
	memset(info, 0, ivsize);

	scatterwalk_map_and_copy(info, req->dst, req->assoclen, ivsize, 1);

	do {
		u64 a;

		memcpy(&a, ctx->salt + ivsize - 8, 8);

		a |= 1;
		a *= seqno;

		memcpy(info + ivsize - 8, &a, 8);
	} while ((ivsize -= 8));

	return crypto_aead_encrypt(subreq);
}