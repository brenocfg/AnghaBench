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
struct TYPE_2__ {int rings; } ;
struct safexcel_crypto_priv {scalar_t__ base; TYPE_1__ config; } ;

/* Variables and functions */
 scalar_t__ EIP197_FLUE_ARC4_OFFSET ; 
 scalar_t__ EIP197_FLUE_CACHEBASE_HI (int) ; 
 scalar_t__ EIP197_FLUE_CACHEBASE_LO (int) ; 
 scalar_t__ EIP197_FLUE_CONFIG (int) ; 
 int /*<<< orphan*/  EIP197_FLUE_CONFIG_MAGIC ; 
 scalar_t__ EIP197_FLUE_IFC_LUT (int) ; 
 scalar_t__ EIP197_FLUE_OFFSETS ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void eip197_trc_cache_setupvirt(struct safexcel_crypto_priv *priv)
{
	int i;

	/*
	 * Map all interfaces/rings to register index 0
	 * so they can share contexts. Without this, the EIP197 will
	 * assume each interface/ring to be in its own memory domain
	 * i.e. have its own subset of UNIQUE memory addresses.
	 * Which would cause records with the SAME memory address to
	 * use DIFFERENT cache buffers, causing both poor cache utilization
	 * AND serious coherence/invalidation issues.
	 */
	for (i = 0; i < 4; i++)
		writel(0, priv->base + EIP197_FLUE_IFC_LUT(i));

	/*
	 * Initialize other virtualization regs for cache
	 * These may not be in their reset state ...
	 */
	for (i = 0; i < priv->config.rings; i++) {
		writel(0, priv->base + EIP197_FLUE_CACHEBASE_LO(i));
		writel(0, priv->base + EIP197_FLUE_CACHEBASE_HI(i));
		writel(EIP197_FLUE_CONFIG_MAGIC,
		       priv->base + EIP197_FLUE_CONFIG(i));
	}
	writel(0, priv->base + EIP197_FLUE_OFFSETS);
	writel(0, priv->base + EIP197_FLUE_ARC4_OFFSET);
}