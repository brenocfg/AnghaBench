#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct device {int dummy; } ;
struct fsl_mc_device {struct device dev; } ;
struct TYPE_16__ {int /*<<< orphan*/  md_acc_num; int /*<<< orphan*/  ptha_acc_num; int /*<<< orphan*/  ccha_acc_num; int /*<<< orphan*/  aes_acc_num; int /*<<< orphan*/  des_acc_num; } ;
struct dpaa2_caam_priv {int /*<<< orphan*/  mc_io; int /*<<< orphan*/ * ppriv; TYPE_5__ sec_attr; int /*<<< orphan*/  domain; } ;
struct TYPE_13__ {int /*<<< orphan*/  cra_driver_name; } ;
struct TYPE_19__ {TYPE_2__ base; } ;
struct TYPE_12__ {scalar_t__ class1_alg_type; struct device* dev; } ;
struct caam_skcipher_alg {int registered; TYPE_8__ skcipher; TYPE_1__ caam; } ;
struct caam_hash_template {int /*<<< orphan*/  driver_name; } ;
struct TYPE_17__ {int /*<<< orphan*/  cra_driver_name; } ;
struct TYPE_18__ {TYPE_6__ base; } ;
struct TYPE_20__ {TYPE_7__ halg; } ;
struct caam_hash_alg {int /*<<< orphan*/  entry; TYPE_9__ ahash_alg; } ;
struct TYPE_15__ {int /*<<< orphan*/  cra_driver_name; } ;
struct TYPE_11__ {TYPE_4__ base; } ;
struct TYPE_14__ {scalar_t__ class1_alg_type; scalar_t__ class2_alg_type; struct device* dev; } ;
struct caam_aead_alg {int registered; TYPE_10__ aead; TYPE_3__ caam; } ;

/* Variables and functions */
 int ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  CAAM_QI_MEMCACHE_SIZE ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct caam_hash_alg*) ; 
 scalar_t__ OP_ALG_ALGSEL_3DES ; 
 scalar_t__ OP_ALG_ALGSEL_AES ; 
 scalar_t__ OP_ALG_ALGSEL_CHACHA20 ; 
 scalar_t__ OP_ALG_ALGSEL_DES ; 
 scalar_t__ OP_ALG_ALGSEL_MASK ; 
 scalar_t__ OP_ALG_ALGSEL_POLY1305 ; 
 scalar_t__ OP_ALG_ALGSEL_SUBMASK ; 
 int PTR_ERR (struct caam_hash_alg*) ; 
 int /*<<< orphan*/  SLAB_CACHE_DMA ; 
 int /*<<< orphan*/ * alloc_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caam_aead_alg_init (struct caam_aead_alg*) ; 
 struct caam_hash_alg* caam_hash_alloc (struct device*,struct caam_hash_template*,int) ; 
 int caam_imx ; 
 int caam_little_end ; 
 int /*<<< orphan*/  caam_skcipher_alg_init (struct caam_skcipher_alg*) ; 
 int crypto_register_aead (TYPE_10__*) ; 
 int crypto_register_ahash (TYPE_9__*) ; 
 int crypto_register_skcipher (TYPE_8__*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct dpaa2_caam_priv*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 struct dpaa2_caam_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int dpaa2_dpseci_bind (struct dpaa2_caam_priv*) ; 
 int /*<<< orphan*/  dpaa2_dpseci_debugfs_init (struct dpaa2_caam_priv*) ; 
 int /*<<< orphan*/  dpaa2_dpseci_dpio_free (struct dpaa2_caam_priv*) ; 
 int dpaa2_dpseci_dpio_setup (struct dpaa2_caam_priv*) ; 
 int dpaa2_dpseci_enable (struct dpaa2_caam_priv*) ; 
 int /*<<< orphan*/  dpaa2_dpseci_free (struct dpaa2_caam_priv*) ; 
 int dpaa2_dpseci_setup (struct fsl_mc_device*) ; 
 void* driver_aeads ; 
 void* driver_algs ; 
 void* driver_hash ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ *) ; 
 int fsl_mc_portal_allocate (struct fsl_mc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_mc_portal_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_list ; 
 int /*<<< orphan*/  iommu_get_domain_for_dev (struct device*) ; 
 int /*<<< orphan*/  kfree (struct caam_hash_alg*) ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qi_cache ; 

__attribute__((used)) static int dpaa2_caam_probe(struct fsl_mc_device *dpseci_dev)
{
	struct device *dev;
	struct dpaa2_caam_priv *priv;
	int i, err = 0;
	bool registered = false;

	/*
	 * There is no way to get CAAM endianness - there is no direct register
	 * space access and MC f/w does not provide this attribute.
	 * All DPAA2-based SoCs have little endian CAAM, thus hard-code this
	 * property.
	 */
	caam_little_end = true;

	caam_imx = false;

	dev = &dpseci_dev->dev;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	dev_set_drvdata(dev, priv);

	priv->domain = iommu_get_domain_for_dev(dev);

	qi_cache = kmem_cache_create("dpaa2_caamqicache", CAAM_QI_MEMCACHE_SIZE,
				     0, SLAB_CACHE_DMA, NULL);
	if (!qi_cache) {
		dev_err(dev, "Can't allocate SEC cache\n");
		return -ENOMEM;
	}

	err = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(49));
	if (err) {
		dev_err(dev, "dma_set_mask_and_coherent() failed\n");
		goto err_dma_mask;
	}

	/* Obtain a MC portal */
	err = fsl_mc_portal_allocate(dpseci_dev, 0, &priv->mc_io);
	if (err) {
		if (err == -ENXIO)
			err = -EPROBE_DEFER;
		else
			dev_err(dev, "MC portal allocation failed\n");

		goto err_dma_mask;
	}

	priv->ppriv = alloc_percpu(*priv->ppriv);
	if (!priv->ppriv) {
		dev_err(dev, "alloc_percpu() failed\n");
		err = -ENOMEM;
		goto err_alloc_ppriv;
	}

	/* DPSECI initialization */
	err = dpaa2_dpseci_setup(dpseci_dev);
	if (err) {
		dev_err(dev, "dpaa2_dpseci_setup() failed\n");
		goto err_dpseci_setup;
	}

	/* DPIO */
	err = dpaa2_dpseci_dpio_setup(priv);
	if (err) {
		if (err != -EPROBE_DEFER)
			dev_err(dev, "dpaa2_dpseci_dpio_setup() failed\n");
		goto err_dpio_setup;
	}

	/* DPSECI binding to DPIO */
	err = dpaa2_dpseci_bind(priv);
	if (err) {
		dev_err(dev, "dpaa2_dpseci_bind() failed\n");
		goto err_bind;
	}

	/* DPSECI enable */
	err = dpaa2_dpseci_enable(priv);
	if (err) {
		dev_err(dev, "dpaa2_dpseci_enable() failed\n");
		goto err_bind;
	}

	dpaa2_dpseci_debugfs_init(priv);

	/* register crypto algorithms the device supports */
	for (i = 0; i < ARRAY_SIZE(driver_algs); i++) {
		struct caam_skcipher_alg *t_alg = driver_algs + i;
		u32 alg_sel = t_alg->caam.class1_alg_type & OP_ALG_ALGSEL_MASK;

		/* Skip DES algorithms if not supported by device */
		if (!priv->sec_attr.des_acc_num &&
		    (alg_sel == OP_ALG_ALGSEL_3DES ||
		     alg_sel == OP_ALG_ALGSEL_DES))
			continue;

		/* Skip AES algorithms if not supported by device */
		if (!priv->sec_attr.aes_acc_num &&
		    alg_sel == OP_ALG_ALGSEL_AES)
			continue;

		/* Skip CHACHA20 algorithms if not supported by device */
		if (alg_sel == OP_ALG_ALGSEL_CHACHA20 &&
		    !priv->sec_attr.ccha_acc_num)
			continue;

		t_alg->caam.dev = dev;
		caam_skcipher_alg_init(t_alg);

		err = crypto_register_skcipher(&t_alg->skcipher);
		if (err) {
			dev_warn(dev, "%s alg registration failed: %d\n",
				 t_alg->skcipher.base.cra_driver_name, err);
			continue;
		}

		t_alg->registered = true;
		registered = true;
	}

	for (i = 0; i < ARRAY_SIZE(driver_aeads); i++) {
		struct caam_aead_alg *t_alg = driver_aeads + i;
		u32 c1_alg_sel = t_alg->caam.class1_alg_type &
				 OP_ALG_ALGSEL_MASK;
		u32 c2_alg_sel = t_alg->caam.class2_alg_type &
				 OP_ALG_ALGSEL_MASK;

		/* Skip DES algorithms if not supported by device */
		if (!priv->sec_attr.des_acc_num &&
		    (c1_alg_sel == OP_ALG_ALGSEL_3DES ||
		     c1_alg_sel == OP_ALG_ALGSEL_DES))
			continue;

		/* Skip AES algorithms if not supported by device */
		if (!priv->sec_attr.aes_acc_num &&
		    c1_alg_sel == OP_ALG_ALGSEL_AES)
			continue;

		/* Skip CHACHA20 algorithms if not supported by device */
		if (c1_alg_sel == OP_ALG_ALGSEL_CHACHA20 &&
		    !priv->sec_attr.ccha_acc_num)
			continue;

		/* Skip POLY1305 algorithms if not supported by device */
		if (c2_alg_sel == OP_ALG_ALGSEL_POLY1305 &&
		    !priv->sec_attr.ptha_acc_num)
			continue;

		/*
		 * Skip algorithms requiring message digests
		 * if MD not supported by device.
		 */
		if ((c2_alg_sel & ~OP_ALG_ALGSEL_SUBMASK) == 0x40 &&
		    !priv->sec_attr.md_acc_num)
			continue;

		t_alg->caam.dev = dev;
		caam_aead_alg_init(t_alg);

		err = crypto_register_aead(&t_alg->aead);
		if (err) {
			dev_warn(dev, "%s alg registration failed: %d\n",
				 t_alg->aead.base.cra_driver_name, err);
			continue;
		}

		t_alg->registered = true;
		registered = true;
	}
	if (registered)
		dev_info(dev, "algorithms registered in /proc/crypto\n");

	/* register hash algorithms the device supports */
	INIT_LIST_HEAD(&hash_list);

	/*
	 * Skip registration of any hashing algorithms if MD block
	 * is not present.
	 */
	if (!priv->sec_attr.md_acc_num)
		return 0;

	for (i = 0; i < ARRAY_SIZE(driver_hash); i++) {
		struct caam_hash_alg *t_alg;
		struct caam_hash_template *alg = driver_hash + i;

		/* register hmac version */
		t_alg = caam_hash_alloc(dev, alg, true);
		if (IS_ERR(t_alg)) {
			err = PTR_ERR(t_alg);
			dev_warn(dev, "%s hash alg allocation failed: %d\n",
				 alg->driver_name, err);
			continue;
		}

		err = crypto_register_ahash(&t_alg->ahash_alg);
		if (err) {
			dev_warn(dev, "%s alg registration failed: %d\n",
				 t_alg->ahash_alg.halg.base.cra_driver_name,
				 err);
			kfree(t_alg);
		} else {
			list_add_tail(&t_alg->entry, &hash_list);
		}

		/* register unkeyed version */
		t_alg = caam_hash_alloc(dev, alg, false);
		if (IS_ERR(t_alg)) {
			err = PTR_ERR(t_alg);
			dev_warn(dev, "%s alg allocation failed: %d\n",
				 alg->driver_name, err);
			continue;
		}

		err = crypto_register_ahash(&t_alg->ahash_alg);
		if (err) {
			dev_warn(dev, "%s alg registration failed: %d\n",
				 t_alg->ahash_alg.halg.base.cra_driver_name,
				 err);
			kfree(t_alg);
		} else {
			list_add_tail(&t_alg->entry, &hash_list);
		}
	}
	if (!list_empty(&hash_list))
		dev_info(dev, "hash algorithms registered in /proc/crypto\n");

	return err;

err_bind:
	dpaa2_dpseci_dpio_free(priv);
err_dpio_setup:
	dpaa2_dpseci_free(priv);
err_dpseci_setup:
	free_percpu(priv->ppriv);
err_alloc_ppriv:
	fsl_mc_portal_free(priv->mc_io);
err_dma_mask:
	kmem_cache_destroy(qi_cache);

	return err;
}