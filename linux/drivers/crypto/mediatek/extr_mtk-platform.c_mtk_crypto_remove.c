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
struct platform_device {int dummy; } ;
struct mtk_cryp {int /*<<< orphan*/  dev; int /*<<< orphan*/  clk_cryp; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_cipher_alg_release (struct mtk_cryp*) ; 
 int /*<<< orphan*/  mtk_desc_dma_free (struct mtk_cryp*) ; 
 int /*<<< orphan*/  mtk_hash_alg_release (struct mtk_cryp*) ; 
 struct mtk_cryp* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_crypto_remove(struct platform_device *pdev)
{
	struct mtk_cryp *cryp = platform_get_drvdata(pdev);

	mtk_hash_alg_release(cryp);
	mtk_cipher_alg_release(cryp);
	mtk_desc_dma_free(cryp);

	clk_disable_unprepare(cryp->clk_cryp);

	pm_runtime_put_sync(cryp->dev);
	pm_runtime_disable(cryp->dev);
	platform_set_drvdata(pdev, NULL);

	return 0;
}