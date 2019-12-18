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
struct nitrox_device {int /*<<< orphan*/ * ctx_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_crypto_dma_pool(struct nitrox_device *ndev)
{
	if (!ndev->ctx_pool)
		return;

	dma_pool_destroy(ndev->ctx_pool);
	ndev->ctx_pool = NULL;
}