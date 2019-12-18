#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* bus_dma_tag_t ;
typedef  int bus_addr_t ;
struct TYPE_3__ {int lowaddr; int highaddr; int alignment; scalar_t__ (* filter ) (int /*<<< orphan*/ ,int) ;struct TYPE_3__* parent; int /*<<< orphan*/  filterarg; } ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
run_filter(bus_dma_tag_t dmat, bus_addr_t paddr)
{
	int retval;

	retval = 0;

	do {
		if (((paddr > dmat->lowaddr && paddr <= dmat->highaddr)
		 || ((paddr & (dmat->alignment - 1)) != 0))
		 && (dmat->filter == NULL
		  || (*dmat->filter)(dmat->filterarg, paddr) != 0))
			retval = 1;

		dmat = dmat->parent;
	} while (retval == 0 && dmat != NULL);
	return (retval);
}