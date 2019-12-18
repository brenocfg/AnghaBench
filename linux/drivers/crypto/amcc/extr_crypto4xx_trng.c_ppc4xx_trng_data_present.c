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
struct hwrng {scalar_t__ priv; } ;
struct crypto4xx_device {scalar_t__ trng_base; } ;

/* Variables and functions */
 scalar_t__ PPC4XX_TRNG_STAT ; 
 int PPC4XX_TRNG_STAT_B ; 
 int in_le32 (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ppc4xx_trng_data_present(struct hwrng *rng, int wait)
{
	struct crypto4xx_device *dev = (void *)rng->priv;
	int busy, i, present = 0;

	for (i = 0; i < 20; i++) {
		busy = (in_le32(dev->trng_base + PPC4XX_TRNG_STAT) &
			PPC4XX_TRNG_STAT_B);
		if (!busy || !wait) {
			present = 1;
			break;
		}
		udelay(10);
	}
	return present;
}