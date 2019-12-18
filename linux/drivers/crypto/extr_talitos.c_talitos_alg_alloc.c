#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct talitos_private {int features; } ;
struct talitos_ctx {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  setkey; } ;
struct crypto_alg {int cra_alignmask; int cra_ctxsize; int /*<<< orphan*/  cra_flags; scalar_t__ cra_priority; int /*<<< orphan*/  cra_module; int /*<<< orphan*/  cra_name; void* cra_exit; int /*<<< orphan*/  cra_init; TYPE_1__ cra_ablkcipher; int /*<<< orphan*/ * cra_type; } ;
struct TYPE_8__ {struct crypto_alg base; } ;
struct TYPE_9__ {int /*<<< orphan*/  init; int /*<<< orphan*/  export; int /*<<< orphan*/  import; int /*<<< orphan*/  setkey; int /*<<< orphan*/  digest; int /*<<< orphan*/  finup; int /*<<< orphan*/  final; int /*<<< orphan*/  update; TYPE_3__ halg; } ;
struct TYPE_7__ {int /*<<< orphan*/  decrypt; int /*<<< orphan*/  encrypt; int /*<<< orphan*/  setkey; int /*<<< orphan*/  init; struct crypto_alg base; } ;
struct TYPE_10__ {TYPE_4__ hash; TYPE_2__ aead; struct crypto_alg crypto; } ;
struct talitos_alg_template {int type; int desc_hdr_template; scalar_t__ priority; TYPE_5__ alg; } ;
struct talitos_crypto_alg {struct device* dev; struct talitos_alg_template algt; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_KERN_DRIVER_ONLY ; 
#define  CRYPTO_ALG_TYPE_ABLKCIPHER 130 
#define  CRYPTO_ALG_TYPE_AEAD 129 
#define  CRYPTO_ALG_TYPE_AHASH 128 
 int DESC_HDR_MODE0_MDEU_SHA256 ; 
 int DESC_HDR_SEL0_MDEUA ; 
 int DESC_HDR_TYPE_COMMON_NONSNOOP_NO_AFEU ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOTSUPP ; 
 struct talitos_crypto_alg* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ TALITOS_CRA_PRIORITY ; 
 int TALITOS_FTR_HMAC_OK ; 
 int TALITOS_FTR_SHA224_HWINIT ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  ablkcipher_decrypt ; 
 int /*<<< orphan*/  ablkcipher_encrypt ; 
 int /*<<< orphan*/  ablkcipher_setkey ; 
 int /*<<< orphan*/  aead_decrypt ; 
 int /*<<< orphan*/  aead_encrypt ; 
 int /*<<< orphan*/  aead_setkey ; 
 int /*<<< orphan*/  ahash_digest ; 
 int /*<<< orphan*/  ahash_export ; 
 int /*<<< orphan*/  ahash_final ; 
 int /*<<< orphan*/  ahash_finup ; 
 int /*<<< orphan*/  ahash_import ; 
 int /*<<< orphan*/  ahash_init ; 
 int /*<<< orphan*/  ahash_init_sha224_swinit ; 
 int /*<<< orphan*/  ahash_setkey ; 
 int /*<<< orphan*/  ahash_update ; 
 int /*<<< orphan*/  crypto_ablkcipher_type ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct talitos_private* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct talitos_crypto_alg*) ; 
 struct talitos_crypto_alg* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ has_ftr_sec1 (struct talitos_private*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 void* talitos_cra_exit ; 
 int /*<<< orphan*/  talitos_cra_init ; 
 int /*<<< orphan*/  talitos_cra_init_aead ; 
 int /*<<< orphan*/  talitos_cra_init_ahash ; 

__attribute__((used)) static struct talitos_crypto_alg *talitos_alg_alloc(struct device *dev,
						    struct talitos_alg_template
						           *template)
{
	struct talitos_private *priv = dev_get_drvdata(dev);
	struct talitos_crypto_alg *t_alg;
	struct crypto_alg *alg;

	t_alg = devm_kzalloc(dev, sizeof(struct talitos_crypto_alg),
			     GFP_KERNEL);
	if (!t_alg)
		return ERR_PTR(-ENOMEM);

	t_alg->algt = *template;

	switch (t_alg->algt.type) {
	case CRYPTO_ALG_TYPE_ABLKCIPHER:
		alg = &t_alg->algt.alg.crypto;
		alg->cra_init = talitos_cra_init;
		alg->cra_exit = talitos_cra_exit;
		alg->cra_type = &crypto_ablkcipher_type;
		alg->cra_ablkcipher.setkey = alg->cra_ablkcipher.setkey ?:
					     ablkcipher_setkey;
		alg->cra_ablkcipher.encrypt = ablkcipher_encrypt;
		alg->cra_ablkcipher.decrypt = ablkcipher_decrypt;
		break;
	case CRYPTO_ALG_TYPE_AEAD:
		alg = &t_alg->algt.alg.aead.base;
		alg->cra_exit = talitos_cra_exit;
		t_alg->algt.alg.aead.init = talitos_cra_init_aead;
		t_alg->algt.alg.aead.setkey = t_alg->algt.alg.aead.setkey ?:
					      aead_setkey;
		t_alg->algt.alg.aead.encrypt = aead_encrypt;
		t_alg->algt.alg.aead.decrypt = aead_decrypt;
		if (!(priv->features & TALITOS_FTR_SHA224_HWINIT) &&
		    !strncmp(alg->cra_name, "authenc(hmac(sha224)", 20)) {
			devm_kfree(dev, t_alg);
			return ERR_PTR(-ENOTSUPP);
		}
		break;
	case CRYPTO_ALG_TYPE_AHASH:
		alg = &t_alg->algt.alg.hash.halg.base;
		alg->cra_init = talitos_cra_init_ahash;
		alg->cra_exit = talitos_cra_exit;
		t_alg->algt.alg.hash.init = ahash_init;
		t_alg->algt.alg.hash.update = ahash_update;
		t_alg->algt.alg.hash.final = ahash_final;
		t_alg->algt.alg.hash.finup = ahash_finup;
		t_alg->algt.alg.hash.digest = ahash_digest;
		if (!strncmp(alg->cra_name, "hmac", 4))
			t_alg->algt.alg.hash.setkey = ahash_setkey;
		t_alg->algt.alg.hash.import = ahash_import;
		t_alg->algt.alg.hash.export = ahash_export;

		if (!(priv->features & TALITOS_FTR_HMAC_OK) &&
		    !strncmp(alg->cra_name, "hmac", 4)) {
			devm_kfree(dev, t_alg);
			return ERR_PTR(-ENOTSUPP);
		}
		if (!(priv->features & TALITOS_FTR_SHA224_HWINIT) &&
		    (!strcmp(alg->cra_name, "sha224") ||
		     !strcmp(alg->cra_name, "hmac(sha224)"))) {
			t_alg->algt.alg.hash.init = ahash_init_sha224_swinit;
			t_alg->algt.desc_hdr_template =
					DESC_HDR_TYPE_COMMON_NONSNOOP_NO_AFEU |
					DESC_HDR_SEL0_MDEUA |
					DESC_HDR_MODE0_MDEU_SHA256;
		}
		break;
	default:
		dev_err(dev, "unknown algorithm type %d\n", t_alg->algt.type);
		devm_kfree(dev, t_alg);
		return ERR_PTR(-EINVAL);
	}

	alg->cra_module = THIS_MODULE;
	if (t_alg->algt.priority)
		alg->cra_priority = t_alg->algt.priority;
	else
		alg->cra_priority = TALITOS_CRA_PRIORITY;
	if (has_ftr_sec1(priv))
		alg->cra_alignmask = 3;
	else
		alg->cra_alignmask = 0;
	alg->cra_ctxsize = sizeof(struct talitos_ctx);
	alg->cra_flags |= CRYPTO_ALG_KERN_DRIVER_ONLY;

	t_alg->dev = dev;

	return t_alg;
}