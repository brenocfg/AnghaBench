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
struct stm32_cryp {int /*<<< orphan*/  clk; int /*<<< orphan*/  dev; int /*<<< orphan*/  list; int /*<<< orphan*/  engine; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  aead_algs ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 TYPE_1__ cryp_list ; 
 int /*<<< orphan*/  crypto_algs ; 
 int /*<<< orphan*/  crypto_engine_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_unregister_aeads (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_unregister_algs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct stm32_cryp* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stm32_cryp_remove(struct platform_device *pdev)
{
	struct stm32_cryp *cryp = platform_get_drvdata(pdev);
	int ret;

	if (!cryp)
		return -ENODEV;

	ret = pm_runtime_get_sync(cryp->dev);
	if (ret < 0)
		return ret;

	crypto_unregister_aeads(aead_algs, ARRAY_SIZE(aead_algs));
	crypto_unregister_algs(crypto_algs, ARRAY_SIZE(crypto_algs));

	crypto_engine_exit(cryp->engine);

	spin_lock(&cryp_list.lock);
	list_del(&cryp->list);
	spin_unlock(&cryp_list.lock);

	pm_runtime_disable(cryp->dev);
	pm_runtime_put_noidle(cryp->dev);

	clk_disable_unprepare(cryp->clk);

	return 0;
}