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
typedef  size_t u32 ;
struct pd_uinfo {TYPE_1__* async_req; } ;
struct crypto4xx_device {struct pd_uinfo* pdr_uinfo; struct ce_pd* pdr; } ;
struct ce_pd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
#define  CRYPTO_ALG_TYPE_AEAD 130 
#define  CRYPTO_ALG_TYPE_AHASH 129 
#define  CRYPTO_ALG_TYPE_SKCIPHER 128 
 int /*<<< orphan*/  crypto4xx_aead_done (struct crypto4xx_device*,struct pd_uinfo*,struct ce_pd*) ; 
 int /*<<< orphan*/  crypto4xx_ahash_done (struct crypto4xx_device*,struct pd_uinfo*) ; 
 int /*<<< orphan*/  crypto4xx_cipher_done (struct crypto4xx_device*,struct pd_uinfo*,struct ce_pd*) ; 
 int crypto_tfm_alg_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crypto4xx_pd_done(struct crypto4xx_device *dev, u32 idx)
{
	struct ce_pd *pd = &dev->pdr[idx];
	struct pd_uinfo *pd_uinfo = &dev->pdr_uinfo[idx];

	switch (crypto_tfm_alg_type(pd_uinfo->async_req->tfm)) {
	case CRYPTO_ALG_TYPE_SKCIPHER:
		crypto4xx_cipher_done(dev, pd_uinfo, pd);
		break;
	case CRYPTO_ALG_TYPE_AEAD:
		crypto4xx_aead_done(dev, pd_uinfo, pd);
		break;
	case CRYPTO_ALG_TYPE_AHASH:
		crypto4xx_ahash_done(dev, pd_uinfo);
		break;
	}
}