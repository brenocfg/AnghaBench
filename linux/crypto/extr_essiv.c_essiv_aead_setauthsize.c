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
struct TYPE_2__ {int /*<<< orphan*/  aead; } ;
struct essiv_tfm_ctx {TYPE_1__ u; } ;
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 struct essiv_tfm_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int crypto_aead_setauthsize (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int essiv_aead_setauthsize(struct crypto_aead *tfm,
				  unsigned int authsize)
{
	struct essiv_tfm_ctx *tctx = crypto_aead_ctx(tfm);

	return crypto_aead_setauthsize(tctx->u.aead, authsize);
}