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
struct bus_dma_tag_common {int lowaddr; int highaddr; int alignment; scalar_t__ (* filter ) (int /*<<< orphan*/ ,int) ;struct bus_dma_tag_common* parent; int /*<<< orphan*/  filterarg; } ;
typedef  int bus_addr_t ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ ,int) ; 

int
bus_dma_run_filter(struct bus_dma_tag_common *tc, bus_addr_t paddr)
{
	int retval;

	retval = 0;
	do {
		if (((paddr > tc->lowaddr && paddr <= tc->highaddr) ||
		    ((paddr & (tc->alignment - 1)) != 0)) &&
		    (tc->filter == NULL ||
		    (*tc->filter)(tc->filterarg, paddr) != 0))
			retval = 1;

		tc = tc->parent;		
	} while (retval == 0 && tc != NULL);
	return (retval);
}