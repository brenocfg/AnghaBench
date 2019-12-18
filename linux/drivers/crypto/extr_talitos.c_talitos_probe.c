#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct talitos_request {int dummy; } ;
struct talitos_private {int num_channels; int chfifo_len; int exec_units; int desc_types; int features; int fifo_len; int /*<<< orphan*/  alg_list; TYPE_1__* chan; scalar_t__* irq; scalar_t__ reg; int /*<<< orphan*/ * done_task; scalar_t__ reg_crcu; scalar_t__ reg_keu; scalar_t__ reg_pkeu; scalar_t__ reg_rngu; scalar_t__ reg_afeu; scalar_t__ reg_mdeu; scalar_t__ reg_aesu; scalar_t__ reg_deu; int /*<<< orphan*/  reg_lock; struct platform_device* ofdev; } ;
struct crypto_alg {int cra_driver_name; } ;
struct TYPE_11__ {struct crypto_alg base; } ;
struct TYPE_15__ {TYPE_2__ halg; } ;
struct TYPE_16__ {struct crypto_alg base; } ;
struct TYPE_12__ {TYPE_7__ hash; TYPE_8__ aead; struct crypto_alg crypto; } ;
struct TYPE_13__ {int type; TYPE_3__ alg; } ;
struct talitos_crypto_alg {int /*<<< orphan*/  entry; TYPE_4__ algt; } ;
struct talitos_channel {int dummy; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  desc_hdr_template; } ;
struct TYPE_10__ {int /*<<< orphan*/  submit_count; void* fifo; int /*<<< orphan*/  tail_lock; int /*<<< orphan*/  head_lock; scalar_t__ reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_5__*) ; 
#define  CRYPTO_ALG_TYPE_ABLKCIPHER 130 
#define  CRYPTO_ALG_TYPE_AEAD 129 
#define  CRYPTO_ALG_TYPE_AHASH 128 
 int /*<<< orphan*/  DESC_HDR_SEL0_RNG ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct talitos_crypto_alg*) ; 
 int PTR_ERR (struct talitos_crypto_alg*) ; 
 scalar_t__ TALITOS10_AESU ; 
 scalar_t__ TALITOS10_AFEU ; 
 scalar_t__ TALITOS10_DEU ; 
 scalar_t__ TALITOS10_MDEU ; 
 scalar_t__ TALITOS10_PKEU ; 
 scalar_t__ TALITOS10_RNGU ; 
 scalar_t__ TALITOS12_AESU ; 
 scalar_t__ TALITOS12_DEU ; 
 scalar_t__ TALITOS12_MDEU ; 
 int TALITOS1_CH_STRIDE ; 
 scalar_t__ TALITOS2_AESU ; 
 scalar_t__ TALITOS2_AFEU ; 
 int TALITOS2_CH_STRIDE ; 
 scalar_t__ TALITOS2_CRCU ; 
 scalar_t__ TALITOS2_DEU ; 
 scalar_t__ TALITOS2_KEU ; 
 scalar_t__ TALITOS2_MDEU ; 
 scalar_t__ TALITOS2_PKEU ; 
 scalar_t__ TALITOS2_RNGU ; 
 scalar_t__ TALITOS_CH_BASE_OFFSET ; 
 int TALITOS_FTR_HMAC_OK ; 
 int TALITOS_FTR_HW_AUTH_CHECK ; 
 int TALITOS_FTR_SEC1 ; 
 int TALITOS_FTR_SHA224_HWINIT ; 
 int TALITOS_FTR_SRC_LINK_TBL_LEN_INCLUDES_EXTENT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int crypto_register_aead (TYPE_8__*) ; 
 int crypto_register_ahash (TYPE_7__*) ; 
 int crypto_register_alg (struct crypto_alg*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct talitos_private*) ; 
 scalar_t__ devm_ioremap (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct talitos_crypto_alg*) ; 
 struct talitos_private* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_set_mask (struct device*,int /*<<< orphan*/ ) ; 
 TYPE_5__* driver_algs ; 
 scalar_t__ has_ftr_sec1 (struct talitos_private*) ; 
 scalar_t__ hw_supports (struct device*,int /*<<< orphan*/ ) ; 
 int init_device (struct device*) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 scalar_t__ of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int roundup_pow_of_two (int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talitos1_done_4ch ; 
 int /*<<< orphan*/  talitos1_done_ch0 ; 
 int /*<<< orphan*/  talitos2_done_4ch ; 
 int /*<<< orphan*/  talitos2_done_ch0 ; 
 int /*<<< orphan*/  talitos2_done_ch0_2 ; 
 int /*<<< orphan*/  talitos2_done_ch1_3 ; 
 struct talitos_crypto_alg* talitos_alg_alloc (struct device*,TYPE_5__*) ; 
 int talitos_probe_irq (struct platform_device*) ; 
 int talitos_register_rng (struct device*) ; 
 int /*<<< orphan*/  talitos_remove (struct platform_device*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int talitos_probe(struct platform_device *ofdev)
{
	struct device *dev = &ofdev->dev;
	struct device_node *np = ofdev->dev.of_node;
	struct talitos_private *priv;
	int i, err;
	int stride;
	struct resource *res;

	priv = devm_kzalloc(dev, sizeof(struct talitos_private), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	INIT_LIST_HEAD(&priv->alg_list);

	dev_set_drvdata(dev, priv);

	priv->ofdev = ofdev;

	spin_lock_init(&priv->reg_lock);

	res = platform_get_resource(ofdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENXIO;
	priv->reg = devm_ioremap(dev, res->start, resource_size(res));
	if (!priv->reg) {
		dev_err(dev, "failed to of_iomap\n");
		err = -ENOMEM;
		goto err_out;
	}

	/* get SEC version capabilities from device tree */
	of_property_read_u32(np, "fsl,num-channels", &priv->num_channels);
	of_property_read_u32(np, "fsl,channel-fifo-len", &priv->chfifo_len);
	of_property_read_u32(np, "fsl,exec-units-mask", &priv->exec_units);
	of_property_read_u32(np, "fsl,descriptor-types-mask",
			     &priv->desc_types);

	if (!is_power_of_2(priv->num_channels) || !priv->chfifo_len ||
	    !priv->exec_units || !priv->desc_types) {
		dev_err(dev, "invalid property data in device tree node\n");
		err = -EINVAL;
		goto err_out;
	}

	if (of_device_is_compatible(np, "fsl,sec3.0"))
		priv->features |= TALITOS_FTR_SRC_LINK_TBL_LEN_INCLUDES_EXTENT;

	if (of_device_is_compatible(np, "fsl,sec2.1"))
		priv->features |= TALITOS_FTR_HW_AUTH_CHECK |
				  TALITOS_FTR_SHA224_HWINIT |
				  TALITOS_FTR_HMAC_OK;

	if (of_device_is_compatible(np, "fsl,sec1.0"))
		priv->features |= TALITOS_FTR_SEC1;

	if (of_device_is_compatible(np, "fsl,sec1.2")) {
		priv->reg_deu = priv->reg + TALITOS12_DEU;
		priv->reg_aesu = priv->reg + TALITOS12_AESU;
		priv->reg_mdeu = priv->reg + TALITOS12_MDEU;
		stride = TALITOS1_CH_STRIDE;
	} else if (of_device_is_compatible(np, "fsl,sec1.0")) {
		priv->reg_deu = priv->reg + TALITOS10_DEU;
		priv->reg_aesu = priv->reg + TALITOS10_AESU;
		priv->reg_mdeu = priv->reg + TALITOS10_MDEU;
		priv->reg_afeu = priv->reg + TALITOS10_AFEU;
		priv->reg_rngu = priv->reg + TALITOS10_RNGU;
		priv->reg_pkeu = priv->reg + TALITOS10_PKEU;
		stride = TALITOS1_CH_STRIDE;
	} else {
		priv->reg_deu = priv->reg + TALITOS2_DEU;
		priv->reg_aesu = priv->reg + TALITOS2_AESU;
		priv->reg_mdeu = priv->reg + TALITOS2_MDEU;
		priv->reg_afeu = priv->reg + TALITOS2_AFEU;
		priv->reg_rngu = priv->reg + TALITOS2_RNGU;
		priv->reg_pkeu = priv->reg + TALITOS2_PKEU;
		priv->reg_keu = priv->reg + TALITOS2_KEU;
		priv->reg_crcu = priv->reg + TALITOS2_CRCU;
		stride = TALITOS2_CH_STRIDE;
	}

	err = talitos_probe_irq(ofdev);
	if (err)
		goto err_out;

	if (has_ftr_sec1(priv)) {
		if (priv->num_channels == 1)
			tasklet_init(&priv->done_task[0], talitos1_done_ch0,
				     (unsigned long)dev);
		else
			tasklet_init(&priv->done_task[0], talitos1_done_4ch,
				     (unsigned long)dev);
	} else {
		if (priv->irq[1]) {
			tasklet_init(&priv->done_task[0], talitos2_done_ch0_2,
				     (unsigned long)dev);
			tasklet_init(&priv->done_task[1], talitos2_done_ch1_3,
				     (unsigned long)dev);
		} else if (priv->num_channels == 1) {
			tasklet_init(&priv->done_task[0], talitos2_done_ch0,
				     (unsigned long)dev);
		} else {
			tasklet_init(&priv->done_task[0], talitos2_done_4ch,
				     (unsigned long)dev);
		}
	}

	priv->chan = devm_kcalloc(dev,
				  priv->num_channels,
				  sizeof(struct talitos_channel),
				  GFP_KERNEL);
	if (!priv->chan) {
		dev_err(dev, "failed to allocate channel management space\n");
		err = -ENOMEM;
		goto err_out;
	}

	priv->fifo_len = roundup_pow_of_two(priv->chfifo_len);

	for (i = 0; i < priv->num_channels; i++) {
		priv->chan[i].reg = priv->reg + stride * (i + 1);
		if (!priv->irq[1] || !(i & 1))
			priv->chan[i].reg += TALITOS_CH_BASE_OFFSET;

		spin_lock_init(&priv->chan[i].head_lock);
		spin_lock_init(&priv->chan[i].tail_lock);

		priv->chan[i].fifo = devm_kcalloc(dev,
						priv->fifo_len,
						sizeof(struct talitos_request),
						GFP_KERNEL);
		if (!priv->chan[i].fifo) {
			dev_err(dev, "failed to allocate request fifo %d\n", i);
			err = -ENOMEM;
			goto err_out;
		}

		atomic_set(&priv->chan[i].submit_count,
			   -(priv->chfifo_len - 1));
	}

	dma_set_mask(dev, DMA_BIT_MASK(36));

	/* reset and initialize the h/w */
	err = init_device(dev);
	if (err) {
		dev_err(dev, "failed to initialize device\n");
		goto err_out;
	}

	/* register the RNG, if available */
	if (hw_supports(dev, DESC_HDR_SEL0_RNG)) {
		err = talitos_register_rng(dev);
		if (err) {
			dev_err(dev, "failed to register hwrng: %d\n", err);
			goto err_out;
		} else
			dev_info(dev, "hwrng\n");
	}

	/* register crypto algorithms the device supports */
	for (i = 0; i < ARRAY_SIZE(driver_algs); i++) {
		if (hw_supports(dev, driver_algs[i].desc_hdr_template)) {
			struct talitos_crypto_alg *t_alg;
			struct crypto_alg *alg = NULL;

			t_alg = talitos_alg_alloc(dev, &driver_algs[i]);
			if (IS_ERR(t_alg)) {
				err = PTR_ERR(t_alg);
				if (err == -ENOTSUPP)
					continue;
				goto err_out;
			}

			switch (t_alg->algt.type) {
			case CRYPTO_ALG_TYPE_ABLKCIPHER:
				err = crypto_register_alg(
						&t_alg->algt.alg.crypto);
				alg = &t_alg->algt.alg.crypto;
				break;

			case CRYPTO_ALG_TYPE_AEAD:
				err = crypto_register_aead(
					&t_alg->algt.alg.aead);
				alg = &t_alg->algt.alg.aead.base;
				break;

			case CRYPTO_ALG_TYPE_AHASH:
				err = crypto_register_ahash(
						&t_alg->algt.alg.hash);
				alg = &t_alg->algt.alg.hash.halg.base;
				break;
			}
			if (err) {
				dev_err(dev, "%s alg registration failed\n",
					alg->cra_driver_name);
				devm_kfree(dev, t_alg);
			} else
				list_add_tail(&t_alg->entry, &priv->alg_list);
		}
	}
	if (!list_empty(&priv->alg_list))
		dev_info(dev, "%s algorithms registered in /proc/crypto\n",
			 (char *)of_get_property(np, "compatible", NULL));

	return 0;

err_out:
	talitos_remove(ofdev);

	return err;
}