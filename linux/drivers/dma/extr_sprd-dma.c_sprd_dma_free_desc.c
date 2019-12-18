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
struct sprd_dma_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sprd_dma_desc*) ; 
 struct sprd_dma_desc* to_sprd_dma_desc (struct virt_dma_desc*) ; 

__attribute__((used)) static void sprd_dma_free_desc(struct virt_dma_desc *vd)
{
	struct sprd_dma_desc *sdesc = to_sprd_dma_desc(vd);

	kfree(sdesc);
}