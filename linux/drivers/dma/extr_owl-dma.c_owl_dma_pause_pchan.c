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
struct owl_dma_pchan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OWL_DMAX_PAUSE ; 
 int /*<<< orphan*/  pchan_writel (struct owl_dma_pchan*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void owl_dma_pause_pchan(struct owl_dma_pchan *pchan)
{
	pchan_writel(pchan, 1, OWL_DMAX_PAUSE);
}