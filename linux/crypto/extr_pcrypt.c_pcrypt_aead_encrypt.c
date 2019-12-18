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
typedef  int u32 ;
struct pcrypt_request {int dummy; } ;
struct pcrypt_aead_ctx {int /*<<< orphan*/  cb_cpu; int /*<<< orphan*/  child; } ;
struct padata_priv {int /*<<< orphan*/  serial; int /*<<< orphan*/  parallel; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int /*<<< orphan*/  assoclen; int /*<<< orphan*/  iv; int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int EINPROGRESS ; 
 struct pcrypt_request* aead_request_ctx (struct aead_request*) ; 
 int aead_request_flags (struct aead_request*) ; 
 int /*<<< orphan*/  aead_request_set_ad (struct aead_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_set_callback (struct aead_request*,int,int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  aead_request_set_crypt (struct aead_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_request_set_tfm (struct aead_request*,int /*<<< orphan*/ ) ; 
 struct pcrypt_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  memset (struct padata_priv*,int /*<<< orphan*/ ,int) ; 
 int padata_do_parallel (int /*<<< orphan*/ ,struct padata_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcrypt_aead_done ; 
 int /*<<< orphan*/  pcrypt_aead_enc ; 
 int /*<<< orphan*/  pcrypt_aead_serial ; 
 struct aead_request* pcrypt_request_ctx (struct pcrypt_request*) ; 
 struct padata_priv* pcrypt_request_padata (struct pcrypt_request*) ; 
 int /*<<< orphan*/  pencrypt ; 

__attribute__((used)) static int pcrypt_aead_encrypt(struct aead_request *req)
{
	int err;
	struct pcrypt_request *preq = aead_request_ctx(req);
	struct aead_request *creq = pcrypt_request_ctx(preq);
	struct padata_priv *padata = pcrypt_request_padata(preq);
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct pcrypt_aead_ctx *ctx = crypto_aead_ctx(aead);
	u32 flags = aead_request_flags(req);

	memset(padata, 0, sizeof(struct padata_priv));

	padata->parallel = pcrypt_aead_enc;
	padata->serial = pcrypt_aead_serial;

	aead_request_set_tfm(creq, ctx->child);
	aead_request_set_callback(creq, flags & ~CRYPTO_TFM_REQ_MAY_SLEEP,
				  pcrypt_aead_done, req);
	aead_request_set_crypt(creq, req->src, req->dst,
			       req->cryptlen, req->iv);
	aead_request_set_ad(creq, req->assoclen);

	err = padata_do_parallel(pencrypt, padata, &ctx->cb_cpu);
	if (!err)
		return -EINPROGRESS;

	return err;
}