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
struct pxad_desc_sw {int nb_desc; struct pxad_desc_hw** hw_desc; } ;
struct pxad_desc_hw {scalar_t__ dtadr; scalar_t__ dsadr; } ;

/* Variables and functions */
 struct pxad_desc_sw* to_pxad_sw_desc (struct virt_dma_desc*) ; 

__attribute__((used)) static bool is_desc_completed(struct virt_dma_desc *vd)
{
	struct pxad_desc_sw *sw_desc = to_pxad_sw_desc(vd);
	struct pxad_desc_hw *updater =
		sw_desc->hw_desc[sw_desc->nb_desc - 1];

	return updater->dtadr != (updater->dsadr + 8);
}