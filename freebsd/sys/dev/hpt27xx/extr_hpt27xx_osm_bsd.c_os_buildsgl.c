#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int sglist_cnt; int /*<<< orphan*/  dxfer_len; scalar_t__ data_ptr; } ;
struct TYPE_10__ {int flags; } ;
union ccb {TYPE_2__ csio; TYPE_1__ ccb_h; } ;
struct TYPE_12__ {int /*<<< orphan*/  ds_len; scalar_t__ ds_addr; } ;
typedef  TYPE_3__ bus_dma_segment_t ;
struct TYPE_15__ {int /*<<< orphan*/  priv; } ;
struct TYPE_14__ {union ccb* ccb; } ;
struct TYPE_13__ {int eot; int /*<<< orphan*/  size; } ;
typedef  TYPE_4__* PSG ;
typedef  TYPE_5__* POS_CMDEXT ;
typedef  TYPE_6__* PCOMMAND ;
typedef  scalar_t__ HPT_UPTR ;
typedef  int /*<<< orphan*/  HPT_U8 ;

/* Variables and functions */
 int CAM_DATA_PHYS ; 
 int CAM_SCATTER_VALID ; 
 int CAM_SG_LIST_PHYS ; 
 int FALSE ; 
 int /*<<< orphan*/  HPT_ASSERT (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  os_set_sgptr (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int os_buildsgl(PCOMMAND pCmd, PSG pSg, int logical)
{
	POS_CMDEXT ext = (POS_CMDEXT)pCmd->priv;
	union ccb *ccb = ext->ccb;
#if (__FreeBSD_version >= 1000510)
	if(logical)	{
		os_set_sgptr(pSg, (HPT_U8 *)ccb->csio.data_ptr);
		pSg->size = ccb->csio.dxfer_len;
		pSg->eot = 1;
		return TRUE;
	}
#else 
	bus_dma_segment_t *sgList = (bus_dma_segment_t *)ccb->csio.data_ptr;
	int idx;

	if(logical)	{
		if (ccb->ccb_h.flags & CAM_DATA_PHYS)
			panic("physical address unsupported");

		if (ccb->ccb_h.flags & CAM_SCATTER_VALID) {
			if (ccb->ccb_h.flags & CAM_SG_LIST_PHYS)
				panic("physical address unsupported");
	
			for (idx = 0; idx < ccb->csio.sglist_cnt; idx++) {
				os_set_sgptr(&pSg[idx], (HPT_U8 *)(HPT_UPTR)sgList[idx].ds_addr);
				pSg[idx].size = sgList[idx].ds_len;
				pSg[idx].eot = (idx==ccb->csio.sglist_cnt-1)? 1 : 0;
			}
		}
		else {
			os_set_sgptr(pSg, (HPT_U8 *)ccb->csio.data_ptr);
			pSg->size = ccb->csio.dxfer_len;
			pSg->eot = 1;
		}
		return TRUE;
	}
#endif
	/* since we have provided physical sg, nobody will ask us to build physical sg */
	HPT_ASSERT(0);
	return FALSE;
}