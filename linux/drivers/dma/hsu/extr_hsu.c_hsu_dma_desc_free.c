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
struct hsu_dma_desc {struct hsu_dma_desc* sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hsu_dma_desc*) ; 
 struct hsu_dma_desc* to_hsu_dma_desc (struct virt_dma_desc*) ; 

__attribute__((used)) static void hsu_dma_desc_free(struct virt_dma_desc *vdesc)
{
	struct hsu_dma_desc *desc = to_hsu_dma_desc(vdesc);

	kfree(desc->sg);
	kfree(desc);
}