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
struct hwrng {unsigned long priv; int /*<<< orphan*/  data_read; int /*<<< orphan*/  data_present; int /*<<< orphan*/  name; } ;
struct device_node {int dummy; } ;
struct crypto4xx_device {int /*<<< orphan*/ * trng_base; } ;
struct crypto4xx_core_device {struct hwrng* trng; int /*<<< orphan*/  device; struct crypto4xx_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int PPC4XX_TRNG_CTRL ; 
 int /*<<< orphan*/  PPC4XX_TRNG_CTRL_DALM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int devm_hwrng_register (int /*<<< orphan*/ ,struct hwrng*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hwrng*) ; 
 struct hwrng* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_device_is_available (struct device_node*) ; 
 struct device_node* of_find_matching_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  out_le32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppc4xx_trng_data_present ; 
 int /*<<< orphan*/  ppc4xx_trng_data_read ; 
 int /*<<< orphan*/  ppc4xx_trng_enable (struct crypto4xx_device*,int) ; 
 int /*<<< orphan*/  ppc4xx_trng_match ; 

void ppc4xx_trng_probe(struct crypto4xx_core_device *core_dev)
{
	struct crypto4xx_device *dev = core_dev->dev;
	struct device_node *trng = NULL;
	struct hwrng *rng = NULL;
	int err;

	/* Find the TRNG device node and map it */
	trng = of_find_matching_node(NULL, ppc4xx_trng_match);
	if (!trng || !of_device_is_available(trng)) {
		of_node_put(trng);
		return;
	}

	dev->trng_base = of_iomap(trng, 0);
	of_node_put(trng);
	if (!dev->trng_base)
		goto err_out;

	rng = kzalloc(sizeof(*rng), GFP_KERNEL);
	if (!rng)
		goto err_out;

	rng->name = KBUILD_MODNAME;
	rng->data_present = ppc4xx_trng_data_present;
	rng->data_read = ppc4xx_trng_data_read;
	rng->priv = (unsigned long) dev;
	core_dev->trng = rng;
	ppc4xx_trng_enable(dev, true);
	out_le32(dev->trng_base + PPC4XX_TRNG_CTRL, PPC4XX_TRNG_CTRL_DALM);
	err = devm_hwrng_register(core_dev->device, core_dev->trng);
	if (err) {
		ppc4xx_trng_enable(dev, false);
		dev_err(core_dev->device, "failed to register hwrng (%d).\n",
			err);
		goto err_out;
	}
	return;

err_out:
	iounmap(dev->trng_base);
	kfree(rng);
	dev->trng_base = NULL;
	core_dev->trng = NULL;
}