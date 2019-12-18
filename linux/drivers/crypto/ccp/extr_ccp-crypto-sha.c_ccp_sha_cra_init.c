#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct crypto_tfm {int dummy; } ;
struct crypto_ahash {int dummy; } ;
struct ccp_sha_req_ctx {int dummy; } ;
struct TYPE_3__ {scalar_t__ key_len; } ;
struct TYPE_4__ {TYPE_1__ sha; } ;
struct ccp_ctx {TYPE_2__ u; int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 struct crypto_ahash* __crypto_ahash_cast (struct crypto_tfm*) ; 
 int /*<<< orphan*/  ccp_sha_complete ; 
 int /*<<< orphan*/  crypto_ahash_set_reqsize (struct crypto_ahash*,int) ; 
 struct ccp_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

__attribute__((used)) static int ccp_sha_cra_init(struct crypto_tfm *tfm)
{
	struct ccp_ctx *ctx = crypto_tfm_ctx(tfm);
	struct crypto_ahash *ahash = __crypto_ahash_cast(tfm);

	ctx->complete = ccp_sha_complete;
	ctx->u.sha.key_len = 0;

	crypto_ahash_set_reqsize(ahash, sizeof(struct ccp_sha_req_ctx));

	return 0;
}