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
struct crypto_aead {int dummy; } ;
struct caam_ctx {unsigned int authsize; } ;

/* Variables and functions */
 struct caam_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int crypto_gcm_check_authsize (unsigned int) ; 
 int /*<<< orphan*/  gcm_set_sh_desc (struct crypto_aead*) ; 

__attribute__((used)) static int gcm_setauthsize(struct crypto_aead *authenc, unsigned int authsize)
{
	struct caam_ctx *ctx = crypto_aead_ctx(authenc);
	int err;

	err = crypto_gcm_check_authsize(authsize);
	if (err)
		return err;

	ctx->authsize = authsize;
	gcm_set_sh_desc(authenc);

	return 0;
}