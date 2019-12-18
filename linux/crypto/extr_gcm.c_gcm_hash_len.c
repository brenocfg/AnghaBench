#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct crypto_gcm_ghash_ctx {int cryptlen; } ;
struct ahash_request {int dummy; } ;
struct TYPE_4__ {struct ahash_request ahreq; } ;
struct crypto_gcm_req_priv_ctx {int /*<<< orphan*/  iauth_tag; int /*<<< orphan*/  sg; struct crypto_gcm_ghash_ctx ghash_ctx; TYPE_1__ u; } ;
struct aead_request {int assoclen; } ;
typedef  int /*<<< orphan*/  lengths ;
struct TYPE_5__ {void* b; void* a; } ;
typedef  TYPE_2__ be128 ;

/* Variables and functions */
 int /*<<< orphan*/  ahash_request_set_callback (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_crypt (struct ahash_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* cpu_to_be64 (int) ; 
 int crypto_ahash_finup (struct ahash_request*) ; 
 struct crypto_gcm_req_priv_ctx* crypto_gcm_reqctx (struct aead_request*) ; 
 int /*<<< orphan*/  gcm_hash_len_done ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gcm_hash_len(struct aead_request *req, u32 flags)
{
	struct crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	struct ahash_request *ahreq = &pctx->u.ahreq;
	struct crypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;
	be128 lengths;

	lengths.a = cpu_to_be64(req->assoclen * 8);
	lengths.b = cpu_to_be64(gctx->cryptlen * 8);
	memcpy(pctx->iauth_tag, &lengths, 16);
	sg_init_one(&pctx->sg, pctx->iauth_tag, 16);
	ahash_request_set_callback(ahreq, flags, gcm_hash_len_done, req);
	ahash_request_set_crypt(ahreq, &pctx->sg,
				pctx->iauth_tag, sizeof(lengths));

	return crypto_ahash_finup(ahreq);
}