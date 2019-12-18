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
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int create_crypto_dma_pool (struct nitrox_device*) ; 
 int /*<<< orphan*/  destroy_crypto_dma_pool (struct nitrox_device*) ; 
 int nitrox_alloc_aqm_queues (struct nitrox_device*) ; 
 int nitrox_alloc_pktin_queues (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_free_pktin_queues (struct nitrox_device*) ; 

int nitrox_common_sw_init(struct nitrox_device *ndev)
{
	int err = 0;

	/* per device crypto context pool */
	err = create_crypto_dma_pool(ndev);
	if (err)
		return err;

	err = nitrox_alloc_pktin_queues(ndev);
	if (err)
		destroy_crypto_dma_pool(ndev);

	err = nitrox_alloc_aqm_queues(ndev);
	if (err) {
		nitrox_free_pktin_queues(ndev);
		destroy_crypto_dma_pool(ndev);
	}

	return err;
}