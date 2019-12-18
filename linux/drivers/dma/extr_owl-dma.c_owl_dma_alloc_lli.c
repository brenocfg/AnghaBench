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
struct owl_dma_lli {int /*<<< orphan*/  phys; int /*<<< orphan*/  node; } ;
struct owl_dma {int /*<<< orphan*/  lli_pool; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct owl_dma_lli* dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct owl_dma_lli *owl_dma_alloc_lli(struct owl_dma *od)
{
	struct owl_dma_lli *lli;
	dma_addr_t phys;

	lli = dma_pool_alloc(od->lli_pool, GFP_NOWAIT, &phys);
	if (!lli)
		return NULL;

	INIT_LIST_HEAD(&lli->node);
	lli->phys = phys;

	return lli;
}