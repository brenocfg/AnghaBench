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
struct ecore_sb_info {int /*<<< orphan*/ * sb_virt; int /*<<< orphan*/  sb_phys; } ;
struct ecore_dev {int dummy; } ;
struct TYPE_3__ {struct ecore_dev cdev; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_DMA_FREE_COHERENT (struct ecore_dev*,void*,int /*<<< orphan*/ ,int) ; 

void
qlnx_free_mem_sb(qlnx_host_t *ha, struct ecore_sb_info *sb_info)
{
	struct ecore_dev	*cdev;

	cdev = &ha->cdev;

        if (sb_info->sb_virt) {
                OSAL_DMA_FREE_COHERENT(cdev, ((void *)sb_info->sb_virt),
			(sb_info->sb_phys), (sizeof(*sb_info->sb_virt)));
		sb_info->sb_virt = NULL;
	}
}