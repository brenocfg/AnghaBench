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
struct owl_dma_vchan {int /*<<< orphan*/ * pchan; } ;
struct owl_dma {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  owl_dma_terminate_pchan (struct owl_dma*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void owl_dma_phy_free(struct owl_dma *od, struct owl_dma_vchan *vchan)
{
	/* Ensure that the physical channel is stopped */
	owl_dma_terminate_pchan(od, vchan->pchan);

	vchan->pchan = NULL;
}