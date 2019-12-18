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
struct rk_crypto_info {int addr_in; int count; int addr_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_WRITE (struct rk_crypto_info*,int /*<<< orphan*/ ,int) ; 
 int RK_CRYPTO_BLOCK_START ; 
 int /*<<< orphan*/  RK_CRYPTO_BRDMAL ; 
 int /*<<< orphan*/  RK_CRYPTO_BRDMAS ; 
 int /*<<< orphan*/  RK_CRYPTO_BTDMAS ; 
 int /*<<< orphan*/  RK_CRYPTO_CTRL ; 
 int _SBF (int,int) ; 

__attribute__((used)) static void crypto_dma_start(struct rk_crypto_info *dev)
{
	CRYPTO_WRITE(dev, RK_CRYPTO_BRDMAS, dev->addr_in);
	CRYPTO_WRITE(dev, RK_CRYPTO_BRDMAL, dev->count / 4);
	CRYPTO_WRITE(dev, RK_CRYPTO_BTDMAS, dev->addr_out);
	CRYPTO_WRITE(dev, RK_CRYPTO_CTRL, RK_CRYPTO_BLOCK_START |
		     _SBF(RK_CRYPTO_BLOCK_START, 16));
}