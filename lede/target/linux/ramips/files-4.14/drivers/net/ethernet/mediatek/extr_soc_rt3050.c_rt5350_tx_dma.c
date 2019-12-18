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
struct fe_tx_dma {scalar_t__ txd4; } ;

/* Variables and functions */

__attribute__((used)) static void rt5350_tx_dma(struct fe_tx_dma *txd)
{
	txd->txd4 = 0;
}