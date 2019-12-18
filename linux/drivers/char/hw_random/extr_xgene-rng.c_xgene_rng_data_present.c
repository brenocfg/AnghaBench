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
typedef  scalar_t__ u32 ;
struct xgene_rng_dev {scalar_t__ csr_base; } ;
struct hwrng {scalar_t__ priv; } ;

/* Variables and functions */
 scalar_t__ READY_MASK ; 
 scalar_t__ RNG_INTR_STS_ACK ; 
 scalar_t__ XGENE_RNG_RETRY_COUNT ; 
 int /*<<< orphan*/  XGENE_RNG_RETRY_INTERVAL ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgene_rng_data_present(struct hwrng *rng, int wait)
{
	struct xgene_rng_dev *ctx = (struct xgene_rng_dev *) rng->priv;
	u32 i, val = 0;

	for (i = 0; i < XGENE_RNG_RETRY_COUNT; i++) {
		val = readl(ctx->csr_base + RNG_INTR_STS_ACK);
		if ((val & READY_MASK) || !wait)
			break;
		udelay(XGENE_RNG_RETRY_INTERVAL);
	}

	return (val & READY_MASK);
}