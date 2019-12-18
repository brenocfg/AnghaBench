#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_8__ {scalar_t__ fmMuramPhysBaseAddr; void* camBaseAddr; TYPE_4__* p_FmDriverParam; int /*<<< orphan*/  h_FmMuram; TYPE_2__* p_FmStateStruct; int /*<<< orphan*/  p_FmDmaRegs; } ;
typedef  TYPE_3__ t_Fm ;
typedef  scalar_t__ t_Error ;
struct TYPE_9__ {int dma_cam_num_of_entries; scalar_t__ cam_base_addr; } ;
struct TYPE_6__ {int majorRev; } ;
struct TYPE_7__ {TYPE_1__ revInfo; } ;

/* Variables and functions */
 int DMA_CAM_ALIGN ; 
 int DMA_CAM_SIZEOF_ENTRY ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  FM_MURAM_AllocMem (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  FM_MURAM_FreeMem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 void* PTR_TO_UINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UINT_TO_PTR (void*) ; 
 int /*<<< orphan*/  WRITE_BLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  WRITE_UINT32 (scalar_t__,int) ; 
 scalar_t__ XX_VirtToPhys (int /*<<< orphan*/ ) ; 
 scalar_t__ fman_dma_init (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static t_Error InitFmDma(t_Fm *p_Fm)
{
    t_Error err;

    err = (t_Error)fman_dma_init(p_Fm->p_FmDmaRegs, p_Fm->p_FmDriverParam);
    if (err != E_OK)
        return err;

    /* Allocate MURAM for CAM */
    p_Fm->camBaseAddr = PTR_TO_UINT(FM_MURAM_AllocMem(p_Fm->h_FmMuram,
                                                      (uint32_t)(p_Fm->p_FmDriverParam->dma_cam_num_of_entries*DMA_CAM_SIZEOF_ENTRY),
                                                      DMA_CAM_ALIGN));
    if (!p_Fm->camBaseAddr)
        RETURN_ERROR(MAJOR, E_NO_MEMORY, ("MURAM alloc for DMA CAM failed"));

    WRITE_BLOCK(UINT_TO_PTR(p_Fm->camBaseAddr),
                0,
                (uint32_t)(p_Fm->p_FmDriverParam->dma_cam_num_of_entries*DMA_CAM_SIZEOF_ENTRY));

    if (p_Fm->p_FmStateStruct->revInfo.majorRev == 2)
    {
        FM_MURAM_FreeMem(p_Fm->h_FmMuram, UINT_TO_PTR(p_Fm->camBaseAddr));

        p_Fm->camBaseAddr = PTR_TO_UINT(FM_MURAM_AllocMem(p_Fm->h_FmMuram,
                                                          (uint32_t)(p_Fm->p_FmDriverParam->dma_cam_num_of_entries*72 + 128),
                                                          64));
        if (!p_Fm->camBaseAddr)
            RETURN_ERROR(MAJOR, E_NO_MEMORY, ("MURAM alloc for DMA CAM failed"));

        WRITE_BLOCK(UINT_TO_PTR(p_Fm->camBaseAddr),
                   0,
               (uint32_t)(p_Fm->p_FmDriverParam->dma_cam_num_of_entries*72 + 128));

        switch(p_Fm->p_FmDriverParam->dma_cam_num_of_entries)
        {
            case (8):
                WRITE_UINT32(*(uint32_t*)p_Fm->camBaseAddr, 0xff000000);
                break;
            case (16):
                WRITE_UINT32(*(uint32_t*)p_Fm->camBaseAddr, 0xffff0000);
                break;
            case (24):
                WRITE_UINT32(*(uint32_t*)p_Fm->camBaseAddr, 0xffffff00);
                break;
            case (32):
                WRITE_UINT32(*(uint32_t*)p_Fm->camBaseAddr, 0xffffffff);
                break;
            default:
                RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("wrong dma_cam_num_of_entries"));
        }
    }

    p_Fm->p_FmDriverParam->cam_base_addr =
                 (uint32_t)(XX_VirtToPhys(UINT_TO_PTR(p_Fm->camBaseAddr)) - p_Fm->fmMuramPhysBaseAddr);

    return E_OK;
}