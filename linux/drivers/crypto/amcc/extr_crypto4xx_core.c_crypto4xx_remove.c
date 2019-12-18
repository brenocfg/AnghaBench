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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct crypto4xx_core_device {int /*<<< orphan*/  rng_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto4xx_stop_all (struct crypto4xx_core_device*) ; 
 int /*<<< orphan*/  crypto4xx_unregister_alg (int /*<<< orphan*/ ) ; 
 struct crypto4xx_core_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppc4xx_trng_remove (struct crypto4xx_core_device*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int crypto4xx_remove(struct platform_device *ofdev)
{
	struct device *dev = &ofdev->dev;
	struct crypto4xx_core_device *core_dev = dev_get_drvdata(dev);

	ppc4xx_trng_remove(core_dev);

	free_irq(core_dev->irq, dev);
	irq_dispose_mapping(core_dev->irq);

	tasklet_kill(&core_dev->tasklet);
	/* Un-register with Linux CryptoAPI */
	crypto4xx_unregister_alg(core_dev->dev);
	mutex_destroy(&core_dev->rng_lock);
	/* Free all allocated memory */
	crypto4xx_stop_all(core_dev);

	return 0;
}