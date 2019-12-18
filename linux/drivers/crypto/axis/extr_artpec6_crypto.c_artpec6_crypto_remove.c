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
struct artpec6_crypto {int /*<<< orphan*/  dma_cache; int /*<<< orphan*/  timer; int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aead_algos ; 
 int /*<<< orphan*/  artpec6_crypto_disable_hw (struct artpec6_crypto*) ; 
 int /*<<< orphan*/  artpec6_crypto_free_debugfs () ; 
 int /*<<< orphan*/  crypto_algos ; 
 int /*<<< orphan*/  crypto_unregister_aeads (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_unregister_ahashes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_unregister_skciphers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ *,int,struct artpec6_crypto*) ; 
 int /*<<< orphan*/  hash_algos ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 struct artpec6_crypto* platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int artpec6_crypto_remove(struct platform_device *pdev)
{
	struct artpec6_crypto *ac = platform_get_drvdata(pdev);
	int irq = platform_get_irq(pdev, 0);

	crypto_unregister_ahashes(hash_algos, ARRAY_SIZE(hash_algos));
	crypto_unregister_skciphers(crypto_algos, ARRAY_SIZE(crypto_algos));
	crypto_unregister_aeads(aead_algos, ARRAY_SIZE(aead_algos));

	tasklet_disable(&ac->task);
	devm_free_irq(&pdev->dev, irq, ac);
	tasklet_kill(&ac->task);
	del_timer_sync(&ac->timer);

	artpec6_crypto_disable_hw(ac);

	kmem_cache_destroy(ac->dma_cache);
#ifdef CONFIG_DEBUG_FS
	artpec6_crypto_free_debugfs();
#endif
	return 0;
}