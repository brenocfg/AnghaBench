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
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned int calc_px (int /*<<< orphan*/ ) ; 
 unsigned int calc_rtx (int /*<<< orphan*/ ) ; 
 unsigned int calc_sx (int /*<<< orphan*/ ) ; 
 unsigned long* dma_get_page_table_origin (unsigned long*) ; 
 unsigned long* dma_get_seg_table_origin (unsigned long*) ; 

unsigned long *dma_walk_cpu_trans(unsigned long *rto, dma_addr_t dma_addr)
{
	unsigned long *sto, *pto;
	unsigned int rtx, sx, px;

	rtx = calc_rtx(dma_addr);
	sto = dma_get_seg_table_origin(&rto[rtx]);
	if (!sto)
		return NULL;

	sx = calc_sx(dma_addr);
	pto = dma_get_page_table_origin(&sto[sx]);
	if (!pto)
		return NULL;

	px = calc_px(dma_addr);
	return &pto[px];
}