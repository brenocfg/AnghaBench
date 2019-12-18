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
struct idma64_hw_desc {int ndesc; struct idma64_hw_desc* hw; int /*<<< orphan*/  llp; int /*<<< orphan*/  lli; } ;
struct idma64_desc {int ndesc; struct idma64_desc* hw; int /*<<< orphan*/  llp; int /*<<< orphan*/  lli; } ;
struct idma64_chan {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct idma64_hw_desc*) ; 

__attribute__((used)) static void idma64_desc_free(struct idma64_chan *idma64c,
		struct idma64_desc *desc)
{
	struct idma64_hw_desc *hw;

	if (desc->ndesc) {
		unsigned int i = desc->ndesc;

		do {
			hw = &desc->hw[--i];
			dma_pool_free(idma64c->pool, hw->lli, hw->llp);
		} while (i);
	}

	kfree(desc->hw);
	kfree(desc);
}