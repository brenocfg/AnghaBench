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
struct TYPE_3__ {int dma; } ;
typedef  TYPE_1__ cx_board_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MASK ; 
 int DMA_MASK_CLEAR ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 

void cx_disable_dma (cx_board_t *b)
{
#ifndef NDIS_MINIPORT_DRIVER
	/* Disable DMA channel. */
	outb (DMA_MASK, (b->dma & 3) | DMA_MASK_CLEAR);
#endif
}