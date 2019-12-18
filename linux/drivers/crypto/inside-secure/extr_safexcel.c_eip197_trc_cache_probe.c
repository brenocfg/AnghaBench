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
typedef  int u32 ;
struct safexcel_crypto_priv {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ EIP197_CLASSIFICATION_RAMS ; 
 int /*<<< orphan*/  eip197_trc_cache_banksel (struct safexcel_crypto_priv*,int,int*) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static u32 eip197_trc_cache_probe(struct safexcel_crypto_priv *priv,
				  int maxbanks, u32 probemask)
{
	u32 val, addrhi, addrlo, addrmid;
	int actbank;

	/*
	 * And probe the actual size of the physically attached cache data RAM
	 * Using a binary subdivision algorithm downto 32 byte cache lines.
	 */
	addrhi = 1 << (16 + maxbanks);
	addrlo = 0;
	actbank = min(maxbanks - 1, 0);
	while ((addrhi - addrlo) > 32) {
		/* write marker to lowest address in top half */
		addrmid = (addrhi + addrlo) >> 1;
		eip197_trc_cache_banksel(priv, addrmid, &actbank);
		writel((addrmid | (addrlo << 16)) & probemask,
			priv->base + EIP197_CLASSIFICATION_RAMS +
			(addrmid & 0xffff));

		/* write marker to lowest address in bottom half */
		eip197_trc_cache_banksel(priv, addrlo, &actbank);
		writel((addrlo | (addrhi << 16)) & probemask,
			priv->base + EIP197_CLASSIFICATION_RAMS +
			(addrlo & 0xffff));

		/* read back marker from top half */
		eip197_trc_cache_banksel(priv, addrmid, &actbank);
		val = readl(priv->base + EIP197_CLASSIFICATION_RAMS +
			    (addrmid & 0xffff));

		if (val == ((addrmid | (addrlo << 16)) & probemask)) {
			/* read back correct, continue with top half */
			addrlo = addrmid;
		} else {
			/* not read back correct, continue with bottom half */
			addrhi = addrmid;
		}
	}
	return addrhi;
}