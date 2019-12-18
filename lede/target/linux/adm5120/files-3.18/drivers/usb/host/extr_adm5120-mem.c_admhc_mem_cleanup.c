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
struct admhcd {int /*<<< orphan*/ * ed_cache; int /*<<< orphan*/ * td_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void admhc_mem_cleanup(struct admhcd *ahcd)
{
	if (ahcd->td_cache) {
		dma_pool_destroy(ahcd->td_cache);
		ahcd->td_cache = NULL;
	}

	if (ahcd->ed_cache) {
		dma_pool_destroy(ahcd->ed_cache);
		ahcd->ed_cache = NULL;
	}
}