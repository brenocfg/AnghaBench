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
struct safexcel_crypto_priv {int /*<<< orphan*/  dev; scalar_t__ base; } ;

/* Variables and functions */
 int EIP197_CS_BANKSEL_MASK ; 
 int EIP197_CS_BANKSEL_OFS ; 
 scalar_t__ EIP197_CS_RAM_CTRL ; 
 int EIP197_CS_TRC_REC_WC ; 
 scalar_t__ EIP197_TRC_ECCCTRL ; 
 int EIP197_TRC_ENABLE_0 ; 
 int EIP197_TRC_ENABLE_MASK ; 
 scalar_t__ EIP197_TRC_FREECHAIN ; 
 int EIP197_TRC_FREECHAIN_HEAD_PTR (int /*<<< orphan*/ ) ; 
 int EIP197_TRC_FREECHAIN_TAIL_PTR (int) ; 
 scalar_t__ EIP197_TRC_PARAMS ; 
 scalar_t__ EIP197_TRC_PARAMS2 ; 
 int EIP197_TRC_PARAMS2_HTABLE_PTR (int) ; 
 int EIP197_TRC_PARAMS2_RC_SZ_SMALL (int) ; 
 int EIP197_TRC_PARAMS_BLK_TIMER_SPEED (int) ; 
 int EIP197_TRC_PARAMS_DATA_ACCESS ; 
 int EIP197_TRC_PARAMS_HTABLE_SZ (int) ; 
 int EIP197_TRC_PARAMS_RC_SZ_LARGE (int) ; 
 int EIP197_TRC_PARAMS_SW_RESET ; 
 int __fls (int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  eip197_trc_cache_clear (struct safexcel_crypto_priv*,int,int) ; 
 int eip197_trc_cache_probe (struct safexcel_crypto_priv*,int,int) ; 
 int /*<<< orphan*/  eip197_trc_cache_setupvirt (struct safexcel_crypto_priv*) ; 
 int min_t (int /*<<< orphan*/ ,int,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  uint ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void eip197_trc_cache_init(struct safexcel_crypto_priv *priv)
{
	u32 val, dsize, asize;
	int cs_rc_max, cs_ht_wc, cs_trc_rec_wc, cs_trc_lg_rec_wc;
	int cs_rc_abs_max, cs_ht_sz;
	int maxbanks;

	/* Setup (dummy) virtualization for cache */
	eip197_trc_cache_setupvirt(priv);

	/*
	 * Enable the record cache memory access and
	 * probe the bank select width
	 */
	val = readl(priv->base + EIP197_CS_RAM_CTRL);
	val &= ~EIP197_TRC_ENABLE_MASK;
	val |= EIP197_TRC_ENABLE_0 | EIP197_CS_BANKSEL_MASK;
	writel(val, priv->base + EIP197_CS_RAM_CTRL);
	val = readl(priv->base + EIP197_CS_RAM_CTRL);
	maxbanks = ((val&EIP197_CS_BANKSEL_MASK)>>EIP197_CS_BANKSEL_OFS) + 1;

	/* Clear all ECC errors */
	writel(0, priv->base + EIP197_TRC_ECCCTRL);

	/*
	 * Make sure the cache memory is accessible by taking record cache into
	 * reset. Need data memory access here, not admin access.
	 */
	val = readl(priv->base + EIP197_TRC_PARAMS);
	val |= EIP197_TRC_PARAMS_SW_RESET | EIP197_TRC_PARAMS_DATA_ACCESS;
	writel(val, priv->base + EIP197_TRC_PARAMS);

	/* Probed data RAM size in bytes */
	dsize = eip197_trc_cache_probe(priv, maxbanks, 0xffffffff);

	/*
	 * Now probe the administration RAM size pretty much the same way
	 * Except that only the lower 30 bits are writable and we don't need
	 * bank selects
	 */
	val = readl(priv->base + EIP197_TRC_PARAMS);
	/* admin access now */
	val &= ~(EIP197_TRC_PARAMS_DATA_ACCESS | EIP197_CS_BANKSEL_MASK);
	writel(val, priv->base + EIP197_TRC_PARAMS);

	/* Probed admin RAM size in admin words */
	asize = eip197_trc_cache_probe(priv, 0, 0xbfffffff) >> 4;

	/* Clear any ECC errors detected while probing! */
	writel(0, priv->base + EIP197_TRC_ECCCTRL);

	/*
	 * Determine optimal configuration from RAM sizes
	 * Note that we assume that the physical RAM configuration is sane
	 * Therefore, we don't do any parameter error checking here ...
	 */

	/* For now, just use a single record format covering everything */
	cs_trc_rec_wc = EIP197_CS_TRC_REC_WC;
	cs_trc_lg_rec_wc = EIP197_CS_TRC_REC_WC;

	/*
	 * Step #1: How many records will physically fit?
	 * Hard upper limit is 1023!
	 */
	cs_rc_abs_max = min_t(uint, ((dsize >> 2) / cs_trc_lg_rec_wc), 1023);
	/* Step #2: Need at least 2 words in the admin RAM per record */
	cs_rc_max = min_t(uint, cs_rc_abs_max, (asize >> 1));
	/* Step #3: Determine log2 of hash table size */
	cs_ht_sz = __fls(asize - cs_rc_max) - 2;
	/* Step #4: determine current size of hash table in dwords */
	cs_ht_wc = 16<<cs_ht_sz; /* dwords, not admin words */
	/* Step #5: add back excess words and see if we can fit more records */
	cs_rc_max = min_t(uint, cs_rc_abs_max, asize - (cs_ht_wc >> 4));

	/* Clear the cache RAMs */
	eip197_trc_cache_clear(priv, cs_rc_max, cs_ht_wc);

	/* Disable the record cache memory access */
	val = readl(priv->base + EIP197_CS_RAM_CTRL);
	val &= ~EIP197_TRC_ENABLE_MASK;
	writel(val, priv->base + EIP197_CS_RAM_CTRL);

	/* Write head and tail pointers of the record free chain */
	val = EIP197_TRC_FREECHAIN_HEAD_PTR(0) |
	      EIP197_TRC_FREECHAIN_TAIL_PTR(cs_rc_max - 1);
	writel(val, priv->base + EIP197_TRC_FREECHAIN);

	/* Configure the record cache #1 */
	val = EIP197_TRC_PARAMS2_RC_SZ_SMALL(cs_trc_rec_wc) |
	      EIP197_TRC_PARAMS2_HTABLE_PTR(cs_rc_max);
	writel(val, priv->base + EIP197_TRC_PARAMS2);

	/* Configure the record cache #2 */
	val = EIP197_TRC_PARAMS_RC_SZ_LARGE(cs_trc_lg_rec_wc) |
	      EIP197_TRC_PARAMS_BLK_TIMER_SPEED(1) |
	      EIP197_TRC_PARAMS_HTABLE_SZ(cs_ht_sz);
	writel(val, priv->base + EIP197_TRC_PARAMS);

	dev_info(priv->dev, "TRC init: %dd,%da (%dr,%dh)\n",
		 dsize, asize, cs_rc_max, cs_ht_wc + cs_ht_wc);
}