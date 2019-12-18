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
typedef  int /*<<< orphan*/  u32 ;
struct ahash_request {int dummy; } ;
struct TYPE_2__ {struct ahash_request ahreq; } ;
struct crypto_gcm_req_priv_ctx {TYPE_1__ u; } ;
struct crypto_gcm_ctx {int /*<<< orphan*/  ghash; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahash_request_set_callback (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aead_request*) ; 
 int /*<<< orphan*/  ahash_request_set_tfm (struct ahash_request*,int /*<<< orphan*/ ) ; 
 struct crypto_gcm_ctx* crypto_aead_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_reqtfm (struct aead_request*) ; 
 scalar_t__ crypto_ahash_init (struct ahash_request*) ; 
 struct crypto_gcm_req_priv_ctx* crypto_gcm_reqctx (struct aead_request*) ; 
 int gcm_hash_init_continue (struct aead_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcm_hash_init_done ; 

__attribute__((used)) static int gcm_hash(struct aead_request *req, u32 flags)
{
	struct crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);
	struct ahash_request *ahreq = &pctx->u.ahreq;
	struct crypto_gcm_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));

	ahash_request_set_tfm(ahreq, ctx->ghash);

	ahash_request_set_callback(ahreq, flags, gcm_hash_init_done, req);
	return crypto_ahash_init(ahreq) ?:
	       gcm_hash_init_continue(req, flags);
}