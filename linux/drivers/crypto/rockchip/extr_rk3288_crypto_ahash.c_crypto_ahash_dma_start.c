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
struct rk_crypto_info {int addr_in; int count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_WRITE (struct rk_crypto_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RK_CRYPTO_CTRL ; 
 int RK_CRYPTO_HASH_START ; 
 int /*<<< orphan*/  RK_CRYPTO_HRDMAL ; 
 int /*<<< orphan*/  RK_CRYPTO_HRDMAS ; 

__attribute__((used)) static void crypto_ahash_dma_start(struct rk_crypto_info *dev)
{
	CRYPTO_WRITE(dev, RK_CRYPTO_HRDMAS, dev->addr_in);
	CRYPTO_WRITE(dev, RK_CRYPTO_HRDMAL, (dev->count + 3) / 4);
	CRYPTO_WRITE(dev, RK_CRYPTO_CTRL, RK_CRYPTO_HASH_START |
					  (RK_CRYPTO_HASH_START << 16));
}