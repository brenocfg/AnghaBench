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
struct virt_dma_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dw_edma_free_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vd2dw_edma_desc (struct virt_dma_desc*) ; 

__attribute__((used)) static void vchan_free_desc(struct virt_dma_desc *vdesc)
{
	dw_edma_free_desc(vd2dw_edma_desc(vdesc));
}