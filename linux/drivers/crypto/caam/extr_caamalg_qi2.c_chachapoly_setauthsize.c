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
 int EINVAL ; 
 unsigned int POLY1305_DIGEST_SIZE ; 
 int chachapoly_set_sh_desc (struct crypto_aead*) ; 
 struct caam_ctx* crypto_aead_ctx (struct crypto_aead*) ; 

__attribute__((used)) static int chachapoly_setauthsize(struct crypto_aead *aead,
				  unsigned int authsize)
{
	struct caam_ctx *ctx = crypto_aead_ctx(aead);

	if (authsize != POLY1305_DIGEST_SIZE)
		return -EINVAL;

	ctx->authsize = authsize;
	return chachapoly_set_sh_desc(aead);
}