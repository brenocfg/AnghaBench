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
typedef  int uint32_t ;
struct TYPE_3__ {int blk_size; } ;
typedef  TYPE_1__ ocs_hw_dif_info_t ;

/* Variables and functions */
#define  OCS_HW_DIF_BK_SIZE_1024 133 
#define  OCS_HW_DIF_BK_SIZE_2048 132 
#define  OCS_HW_DIF_BK_SIZE_4096 131 
#define  OCS_HW_DIF_BK_SIZE_4104 130 
#define  OCS_HW_DIF_BK_SIZE_512 129 
#define  OCS_HW_DIF_BK_SIZE_520 128 

uint32_t
ocs_hw_dif_blocksize(ocs_hw_dif_info_t *dif_info)
{
	uint32_t blocksize = 0;

	switch(dif_info->blk_size) {
	case OCS_HW_DIF_BK_SIZE_512:	blocksize = 512; break;
	case OCS_HW_DIF_BK_SIZE_1024:	blocksize = 1024; break;
	case OCS_HW_DIF_BK_SIZE_2048:	blocksize = 2048; break;
	case OCS_HW_DIF_BK_SIZE_4096:	blocksize = 4096; break;
	case OCS_HW_DIF_BK_SIZE_520:	blocksize = 520; break;
	case OCS_HW_DIF_BK_SIZE_4104:	blocksize = 4104; break;
	default:
		break;
	}

	return blocksize;
}