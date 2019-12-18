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
struct ccp_sg_workarea {scalar_t__ dma_count; int /*<<< orphan*/  dma_dir; int /*<<< orphan*/  nents; int /*<<< orphan*/  dma_sg; int /*<<< orphan*/  dma_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccp_sg_free(struct ccp_sg_workarea *wa)
{
	if (wa->dma_count)
		dma_unmap_sg(wa->dma_dev, wa->dma_sg, wa->nents, wa->dma_dir);

	wa->dma_count = 0;
}