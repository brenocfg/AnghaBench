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
typedef  int /*<<< orphan*/  iflib_dma_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  iflib_dma_free (int /*<<< orphan*/ ) ; 

void
iflib_dma_free_multi(iflib_dma_info_t *dmalist, int count)
{
	int i;
	iflib_dma_info_t *dmaiter = dmalist;

	for (i = 0; i < count; i++, dmaiter++)
		iflib_dma_free(*dmaiter);
}