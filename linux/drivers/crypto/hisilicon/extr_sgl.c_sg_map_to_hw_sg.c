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
struct scatterlist {int /*<<< orphan*/  dma_length; int /*<<< orphan*/  dma_address; } ;
struct acc_hw_sge {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */

__attribute__((used)) static void sg_map_to_hw_sg(struct scatterlist *sgl,
			    struct acc_hw_sge *hw_sge)
{
	hw_sge->buf = sgl->dma_address;
	hw_sge->len = sgl->dma_length;
}