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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mtk_cryp {scalar_t__* irq; int /*<<< orphan*/ * dev; int /*<<< orphan*/  clk_cryp; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MTK_IRQ_NUM ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 struct mtk_cryp* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int mtk_accelerator_init (struct mtk_cryp*) ; 
 int mtk_cipher_alg_register (struct mtk_cryp*) ; 
 int /*<<< orphan*/  mtk_cipher_alg_release (struct mtk_cryp*) ; 
 int /*<<< orphan*/  mtk_desc_dma_free (struct mtk_cryp*) ; 
 int mtk_desc_ring_alloc (struct mtk_cryp*) ; 
 int /*<<< orphan*/  mtk_dfe_dse_reset (struct mtk_cryp*) ; 
 int mtk_hash_alg_register (struct mtk_cryp*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk_cryp*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtk_crypto_probe(struct platform_device *pdev)
{
	struct mtk_cryp *cryp;
	int i, err;

	cryp = devm_kzalloc(&pdev->dev, sizeof(*cryp), GFP_KERNEL);
	if (!cryp)
		return -ENOMEM;

	cryp->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(cryp->base))
		return PTR_ERR(cryp->base);

	for (i = 0; i < MTK_IRQ_NUM; i++) {
		cryp->irq[i] = platform_get_irq(pdev, i);
		if (cryp->irq[i] < 0)
			return cryp->irq[i];
	}

	cryp->clk_cryp = devm_clk_get(&pdev->dev, "cryp");
	if (IS_ERR(cryp->clk_cryp))
		return -EPROBE_DEFER;

	cryp->dev = &pdev->dev;
	pm_runtime_enable(cryp->dev);
	pm_runtime_get_sync(cryp->dev);

	err = clk_prepare_enable(cryp->clk_cryp);
	if (err)
		goto err_clk_cryp;

	/* Allocate four command/result descriptor rings */
	err = mtk_desc_ring_alloc(cryp);
	if (err) {
		dev_err(cryp->dev, "Unable to allocate descriptor rings.\n");
		goto err_resource;
	}

	/* Initialize hardware modules */
	err = mtk_accelerator_init(cryp);
	if (err) {
		dev_err(cryp->dev, "Failed to initialize cryptographic engine.\n");
		goto err_engine;
	}

	err = mtk_cipher_alg_register(cryp);
	if (err) {
		dev_err(cryp->dev, "Unable to register cipher algorithm.\n");
		goto err_cipher;
	}

	err = mtk_hash_alg_register(cryp);
	if (err) {
		dev_err(cryp->dev, "Unable to register hash algorithm.\n");
		goto err_hash;
	}

	platform_set_drvdata(pdev, cryp);
	return 0;

err_hash:
	mtk_cipher_alg_release(cryp);
err_cipher:
	mtk_dfe_dse_reset(cryp);
err_engine:
	mtk_desc_dma_free(cryp);
err_resource:
	clk_disable_unprepare(cryp->clk_cryp);
err_clk_cryp:
	pm_runtime_put_sync(cryp->dev);
	pm_runtime_disable(cryp->dev);

	return err;
}