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
struct safexcel_crypto_priv {int base; } ;

/* Variables and functions */
 int EIP197_CLASSIFICATION_RAMS ; 
 int EIP197_CS_RC_NEXT (int) ; 
 int EIP197_CS_RC_PREV (int) ; 
 int EIP197_CS_RC_SIZE ; 
 int EIP197_RC_NULL ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static void eip197_trc_cache_clear(struct safexcel_crypto_priv *priv,
				   int cs_rc_max, int cs_ht_wc)
{
	int i;
	u32 htable_offset, val, offset;

	/* Clear all records in administration RAM */
	for (i = 0; i < cs_rc_max; i++) {
		offset = EIP197_CLASSIFICATION_RAMS + i * EIP197_CS_RC_SIZE;

		writel(EIP197_CS_RC_NEXT(EIP197_RC_NULL) |
		       EIP197_CS_RC_PREV(EIP197_RC_NULL),
		       priv->base + offset);

		val = EIP197_CS_RC_NEXT(i + 1) | EIP197_CS_RC_PREV(i - 1);
		if (i == 0)
			val |= EIP197_CS_RC_PREV(EIP197_RC_NULL);
		else if (i == cs_rc_max - 1)
			val |= EIP197_CS_RC_NEXT(EIP197_RC_NULL);
		writel(val, priv->base + offset + 4);
		/* must also initialize the address key due to ECC! */
		writel(0, priv->base + offset + 8);
		writel(0, priv->base + offset + 12);
	}

	/* Clear the hash table entries */
	htable_offset = cs_rc_max * EIP197_CS_RC_SIZE;
	for (i = 0; i < cs_ht_wc; i++)
		writel(GENMASK(29, 0),
		       priv->base + EIP197_CLASSIFICATION_RAMS +
		       htable_offset + i * sizeof(u32));
}