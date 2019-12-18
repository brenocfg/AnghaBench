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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ priv; } ;
struct mtk_rng {TYPE_1__ rng; scalar_t__ base; } ;
struct hwrng {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ RNG_DATA ; 
 int /*<<< orphan*/  mtk_rng_wait_ready (struct hwrng*,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync_autosuspend (struct device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct mtk_rng* to_mtk_rng (struct hwrng*) ; 

__attribute__((used)) static int mtk_rng_read(struct hwrng *rng, void *buf, size_t max, bool wait)
{
	struct mtk_rng *priv = to_mtk_rng(rng);
	int retval = 0;

	pm_runtime_get_sync((struct device *)priv->rng.priv);

	while (max >= sizeof(u32)) {
		if (!mtk_rng_wait_ready(rng, wait))
			break;

		*(u32 *)buf = readl(priv->base + RNG_DATA);
		retval += sizeof(u32);
		buf += sizeof(u32);
		max -= sizeof(u32);
	}

	pm_runtime_mark_last_busy((struct device *)priv->rng.priv);
	pm_runtime_put_sync_autosuspend((struct device *)priv->rng.priv);

	return retval || !wait ? retval : -EIO;
}