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
struct dw_dma {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_dw_dma_on (struct dw_dma*) ; 
 int /*<<< orphan*/  idma32_fifo_partition (struct dw_dma*) ; 

__attribute__((used)) static void idma32_enable(struct dw_dma *dw)
{
	idma32_fifo_partition(dw);
	do_dw_dma_on(dw);
}