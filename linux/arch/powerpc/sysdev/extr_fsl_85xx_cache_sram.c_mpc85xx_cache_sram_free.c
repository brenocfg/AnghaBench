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
struct TYPE_2__ {int base_virt; int /*<<< orphan*/  lock; int /*<<< orphan*/  rh; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_1__* cache_sram ; 
 int /*<<< orphan*/  rh_free (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mpc85xx_cache_sram_free(void *ptr)
{
	unsigned long flags;
	BUG_ON(!ptr);

	spin_lock_irqsave(&cache_sram->lock, flags);
	rh_free(cache_sram->rh, ptr - cache_sram->base_virt);
	spin_unlock_irqrestore(&cache_sram->lock, flags);
}