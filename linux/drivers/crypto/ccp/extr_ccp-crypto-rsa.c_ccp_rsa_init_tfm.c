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
struct crypto_akcipher {int dummy; } ;
struct ccp_rsa_req_ctx {int dummy; } ;
struct ccp_ctx {int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  akcipher_set_reqsize (struct crypto_akcipher*,int) ; 
 struct ccp_ctx* akcipher_tfm_ctx (struct crypto_akcipher*) ; 
 int /*<<< orphan*/  ccp_rsa_complete ; 

__attribute__((used)) static int ccp_rsa_init_tfm(struct crypto_akcipher *tfm)
{
	struct ccp_ctx *ctx = akcipher_tfm_ctx(tfm);

	akcipher_set_reqsize(tfm, sizeof(struct ccp_rsa_req_ctx));
	ctx->complete = ccp_rsa_complete;

	return 0;
}