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
typedef  int u32 ;
struct ks_sa_rng {TYPE_1__* reg_rng; } ;
struct hwrng {scalar_t__ priv; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int SA_MAX_RNG_DATA_RETRIES ; 
 int /*<<< orphan*/  SA_RNG_DATA_RETRY_DELAY ; 
 int TRNG_STATUS_REG_READY ; 
 struct ks_sa_rng* dev_get_drvdata (struct device*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ks_sa_rng_data_present(struct hwrng *rng, int wait)
{
	struct device *dev = (struct device *)rng->priv;
	struct ks_sa_rng *ks_sa_rng = dev_get_drvdata(dev);

	u32	ready;
	int	j;

	for (j = 0; j < SA_MAX_RNG_DATA_RETRIES; j++) {
		ready = readl(&ks_sa_rng->reg_rng->status);
		ready &= TRNG_STATUS_REG_READY;

		if (ready || !wait)
			break;

		udelay(SA_RNG_DATA_RETRY_DELAY);
	}

	return ready;
}