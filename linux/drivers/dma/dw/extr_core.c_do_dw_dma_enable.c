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
struct dw_dma_chip {struct dw_dma* dw; } ;
struct dw_dma {int /*<<< orphan*/  (* enable ) (struct dw_dma*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct dw_dma*) ; 

int do_dw_dma_enable(struct dw_dma_chip *chip)
{
	struct dw_dma *dw = chip->dw;

	dw->enable(dw);
	return 0;
}