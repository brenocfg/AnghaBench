#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct simd_aead_ctx {TYPE_1__* cryptd_tfm; } ;
struct crypto_aead {int dummy; } ;
struct aead_request {int dummy; } ;
struct TYPE_3__ {struct crypto_aead base; } ;

/* Variables and functions */
 struct aead_request* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  aead_request_set_tfm (struct aead_request*,struct crypto_aead*) ; 
 struct crypto_aead* cryptd_aead_child (TYPE_1__*) ; 
 scalar_t__ cryptd_aead_queued (TYPE_1__*) ; 
 struct simd_aead_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int crypto_aead_encrypt (struct aead_request*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  crypto_simd_usable () ; 
 scalar_t__ in_atomic () ; 

__attribute__((used)) static int simd_aead_encrypt(struct aead_request *req)
{
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	struct simd_aead_ctx *ctx = crypto_aead_ctx(tfm);
	struct aead_request *subreq;
	struct crypto_aead *child;

	subreq = aead_request_ctx(req);
	*subreq = *req;

	if (!crypto_simd_usable() ||
	    (in_atomic() && cryptd_aead_queued(ctx->cryptd_tfm)))
		child = &ctx->cryptd_tfm->base;
	else
		child = cryptd_aead_child(ctx->cryptd_tfm);

	aead_request_set_tfm(subreq, child);

	return crypto_aead_encrypt(subreq);
}