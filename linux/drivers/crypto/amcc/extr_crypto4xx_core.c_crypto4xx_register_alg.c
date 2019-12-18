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
struct crypto4xx_device {int /*<<< orphan*/  alg_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  cipher; int /*<<< orphan*/  rng; int /*<<< orphan*/  hash; int /*<<< orphan*/  aead; } ;
struct crypto4xx_alg_common {int type; TYPE_1__ u; } ;
struct crypto4xx_alg {int /*<<< orphan*/  entry; struct crypto4xx_alg_common alg; struct crypto4xx_device* dev; } ;

/* Variables and functions */
#define  CRYPTO_ALG_TYPE_AEAD 130 
#define  CRYPTO_ALG_TYPE_AHASH 129 
#define  CRYPTO_ALG_TYPE_RNG 128 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int crypto_register_aead (int /*<<< orphan*/ *) ; 
 int crypto_register_ahash (int /*<<< orphan*/ *) ; 
 int crypto_register_rng (int /*<<< orphan*/ *) ; 
 int crypto_register_skcipher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct crypto4xx_alg*) ; 
 struct crypto4xx_alg* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int crypto4xx_register_alg(struct crypto4xx_device *sec_dev,
				  struct crypto4xx_alg_common *crypto_alg,
				  int array_size)
{
	struct crypto4xx_alg *alg;
	int i;
	int rc = 0;

	for (i = 0; i < array_size; i++) {
		alg = kzalloc(sizeof(struct crypto4xx_alg), GFP_KERNEL);
		if (!alg)
			return -ENOMEM;

		alg->alg = crypto_alg[i];
		alg->dev = sec_dev;

		switch (alg->alg.type) {
		case CRYPTO_ALG_TYPE_AEAD:
			rc = crypto_register_aead(&alg->alg.u.aead);
			break;

		case CRYPTO_ALG_TYPE_AHASH:
			rc = crypto_register_ahash(&alg->alg.u.hash);
			break;

		case CRYPTO_ALG_TYPE_RNG:
			rc = crypto_register_rng(&alg->alg.u.rng);
			break;

		default:
			rc = crypto_register_skcipher(&alg->alg.u.cipher);
			break;
		}

		if (rc)
			kfree(alg);
		else
			list_add_tail(&alg->entry, &sec_dev->alg_list);
	}

	return 0;
}