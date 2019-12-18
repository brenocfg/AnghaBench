#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int cd_size; int pes; int rings; int cd_offset; } ;
struct TYPE_7__ {int hwdataw; int hwcfsize; } ;
struct safexcel_crypto_priv {int flags; TYPE_4__ config; TYPE_3__ hwconfig; TYPE_2__* ring; } ;
struct TYPE_5__ {int /*<<< orphan*/  base_dma; } ;
struct TYPE_6__ {TYPE_1__ cdr; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EIP197_FETCH_DEPTH ; 
 scalar_t__ EIP197_HIA_CDR (struct safexcel_crypto_priv*,int) ; 
 scalar_t__ EIP197_HIA_xDR_CFG ; 
 int EIP197_HIA_xDR_CFG_RD_CACHE (int /*<<< orphan*/ ) ; 
 int EIP197_HIA_xDR_CFG_WR_CACHE (int /*<<< orphan*/ ) ; 
 scalar_t__ EIP197_HIA_xDR_DESC_SIZE ; 
 scalar_t__ EIP197_HIA_xDR_DMA_CFG ; 
 scalar_t__ EIP197_HIA_xDR_RING_BASE_ADDR_HI ; 
 scalar_t__ EIP197_HIA_xDR_RING_BASE_ADDR_LO ; 
 scalar_t__ EIP197_HIA_xDR_STAT ; 
 int EIP197_xDR_DESC_MODE_64BIT ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RD_CACHE_3BITS ; 
 int SAFEXCEL_HW_EIP197 ; 
 int /*<<< orphan*/  WR_CACHE_3BITS ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int min_t (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  uint ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int safexcel_hw_setup_cdesc_rings(struct safexcel_crypto_priv *priv)
{
	u32 cd_size_rnd, val;
	int i, cd_fetch_cnt;

	cd_size_rnd  = (priv->config.cd_size +
			(BIT(priv->hwconfig.hwdataw) - 1)) >>
		       priv->hwconfig.hwdataw;
	/* determine number of CD's we can fetch into the CD FIFO as 1 block */
	if (priv->flags & SAFEXCEL_HW_EIP197) {
		/* EIP197: try to fetch enough in 1 go to keep all pipes busy */
		cd_fetch_cnt = (1 << priv->hwconfig.hwcfsize) / cd_size_rnd;
		cd_fetch_cnt = min_t(uint, cd_fetch_cnt,
				     (priv->config.pes * EIP197_FETCH_DEPTH));
	} else {
		/* for the EIP97, just fetch all that fits minus 1 */
		cd_fetch_cnt = ((1 << priv->hwconfig.hwcfsize) /
				cd_size_rnd) - 1;
	}

	for (i = 0; i < priv->config.rings; i++) {
		/* ring base address */
		writel(lower_32_bits(priv->ring[i].cdr.base_dma),
		       EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_RING_BASE_ADDR_LO);
		writel(upper_32_bits(priv->ring[i].cdr.base_dma),
		       EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_RING_BASE_ADDR_HI);

		writel(EIP197_xDR_DESC_MODE_64BIT | (priv->config.cd_offset << 16) |
		       priv->config.cd_size,
		       EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_DESC_SIZE);
		writel(((cd_fetch_cnt *
			 (cd_size_rnd << priv->hwconfig.hwdataw)) << 16) |
		       (cd_fetch_cnt * priv->config.cd_offset),
		       EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_CFG);

		/* Configure DMA tx control */
		val = EIP197_HIA_xDR_CFG_WR_CACHE(WR_CACHE_3BITS);
		val |= EIP197_HIA_xDR_CFG_RD_CACHE(RD_CACHE_3BITS);
		writel(val, EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_DMA_CFG);

		/* clear any pending interrupt */
		writel(GENMASK(5, 0),
		       EIP197_HIA_CDR(priv, i) + EIP197_HIA_xDR_STAT);
	}

	return 0;
}