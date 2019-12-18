#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u16 ;
struct status_block_e4 {int dummy; } ;
struct ecore_sb_info {int dummy; } ;
struct ecore_dev {int dummy; } ;
struct TYPE_4__ {struct ecore_dev cdev; } ;
typedef  TYPE_1__ qlnx_host_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct status_block_e4* OSAL_DMA_ALLOC_COHERENT (struct ecore_dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OSAL_DMA_FREE_COHERENT (struct ecore_dev*,struct status_block_e4*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  QL_DPRINT1 (TYPE_1__*,char*) ; 
 int qlnx_sb_init (struct ecore_dev*,struct ecore_sb_info*,struct status_block_e4*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
qlnx_alloc_mem_sb(qlnx_host_t *ha, struct ecore_sb_info *sb_info, u16 sb_id)
{
        struct status_block_e4	*sb_virt;
        bus_addr_t		sb_phys;
        int			rc;
	uint32_t		size;
	struct ecore_dev	*cdev;

	cdev = &ha->cdev;

	size = sizeof(*sb_virt);
	sb_virt = OSAL_DMA_ALLOC_COHERENT(cdev, (&sb_phys), size);

        if (!sb_virt) {
                QL_DPRINT1(ha, "Status block allocation failed\n");
                return -ENOMEM;
        }

        rc = qlnx_sb_init(cdev, sb_info, sb_virt, sb_phys, sb_id);
        if (rc) {
                OSAL_DMA_FREE_COHERENT(cdev, sb_virt, sb_phys, size);
        }

	return rc;
}