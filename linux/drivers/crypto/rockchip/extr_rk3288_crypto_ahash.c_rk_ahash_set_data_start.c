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
struct rk_crypto_info {int (* load_data ) (struct rk_crypto_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  sg_src; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_ahash_dma_start (struct rk_crypto_info*) ; 
 int stub1 (struct rk_crypto_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rk_ahash_set_data_start(struct rk_crypto_info *dev)
{
	int err;

	err = dev->load_data(dev, dev->sg_src, NULL);
	if (!err)
		crypto_ahash_dma_start(dev);
	return err;
}