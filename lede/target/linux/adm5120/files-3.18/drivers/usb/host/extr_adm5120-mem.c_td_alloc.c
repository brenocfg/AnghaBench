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
struct td {int /*<<< orphan*/  td_dma; int /*<<< orphan*/  hwNextTD; } ;
struct admhcd {int /*<<< orphan*/  td_cache; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_hc32 (struct admhcd*,int /*<<< orphan*/ ) ; 
 struct td* dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct td*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct td *td_alloc(struct admhcd *ahcd, gfp_t mem_flags)
{
	dma_addr_t	dma;
	struct td	*td;

	td = dma_pool_alloc(ahcd->td_cache, mem_flags, &dma);
	if (!td)
		return NULL;

	/* in case ahcd fetches it, make it look dead */
	memset(td, 0, sizeof *td);
	td->hwNextTD = cpu_to_hc32(ahcd, dma);
	td->td_dma = dma;
	/* hashed in td_fill */

	return td;
}