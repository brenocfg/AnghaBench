#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  t_Handle ;
struct TYPE_11__ {int sizeForFragmentation; int dontFragAction; int sgBpid; int scratchBpid; scalar_t__ sgBpidEn; } ;
typedef  TYPE_2__ t_FmPcdManipFragIpParams ;
struct TYPE_10__ {int scratchBpid; TYPE_5__* p_Frag; } ;
struct TYPE_12__ {int h_Ad; int sizeForFragmentation; TYPE_1__ fragParams; int /*<<< orphan*/  frag; TYPE_4__* h_FmPcd; } ;
typedef  TYPE_3__ t_FmPcdManip ;
struct TYPE_13__ {int /*<<< orphan*/  h_FmMuram; scalar_t__ physicalMuramBase; int /*<<< orphan*/  ipv6FrameIdAddr; } ;
typedef  TYPE_4__ t_FmPcd ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_14__ {int /*<<< orphan*/  gmask; int /*<<< orphan*/  ccAdBase; int /*<<< orphan*/  pcAndOffsets; } ;
typedef  TYPE_5__ t_AdOfTypeContLookup ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  E_OK ; 
 scalar_t__ FM_MURAM_AllocMem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_MURAM_FreeMem (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int FM_PCD_AD_CONT_LOOKUP_TYPE ; 
 int /*<<< orphan*/  FM_PCD_CC_AD_ENTRY_SIZE ; 
 int /*<<< orphan*/  FM_PCD_CC_AD_TABLE_ALIGN ; 
 int FM_PCD_MANIP_IP_FRAG_DF_SHIFT ; 
 int FM_PCD_MANIP_IP_FRAG_SCRATCH_BPID ; 
 int FM_PCD_MANIP_IP_FRAG_SG_BDID_EN ; 
 int FM_PCD_MANIP_IP_FRAG_SG_BDID_MASK ; 
 int FM_PCD_MANIP_IP_FRAG_SG_BDID_SHIFT ; 
 int /*<<< orphan*/  FmPcdFragHcScratchPoolFill (int /*<<< orphan*/ ,int) ; 
 scalar_t__ HMAN_OC_IP_FRAGMENTATION ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MemSet8 (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UINT_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ XX_VirtToPhys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static t_Error IpFragmentation(t_FmPcdManipFragIpParams *p_ManipParams,
                               t_FmPcdManip *p_Manip)
{
    uint32_t pcAndOffsetsReg = 0, ccAdBaseReg = 0, gmaskReg = 0;
    t_FmPcd *p_FmPcd;
#if (DPAA_VERSION == 10)
    t_Error err = E_OK;
#endif /* (DPAA_VERSION == 10) */

    SANITY_CHECK_RETURN_ERROR(p_Manip->h_Ad, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_ManipParams->sizeForFragmentation != 0xFFFF,
                              E_INVALID_VALUE);

    p_FmPcd = p_Manip->h_FmPcd;
    /* Allocation of fragmentation Action Descriptor */
    p_Manip->fragParams.p_Frag = (t_AdOfTypeContLookup *)FM_MURAM_AllocMem(
            p_FmPcd->h_FmMuram, FM_PCD_CC_AD_ENTRY_SIZE,
            FM_PCD_CC_AD_TABLE_ALIGN);
    if (!p_Manip->fragParams.p_Frag)
        RETURN_ERROR(MAJOR, E_NO_MEMORY,
                     ("MURAM alloc for Fragmentation table descriptor"));
    MemSet8(p_Manip->fragParams.p_Frag, 0, FM_PCD_CC_AD_ENTRY_SIZE);

    /* Prepare the third Ad register (pcAndOffsets)- OperationCode */
    pcAndOffsetsReg = (uint32_t)HMAN_OC_IP_FRAGMENTATION;

    /* Prepare the first Ad register (ccAdBase) - Don't frag action and Action descriptor type*/
    ccAdBaseReg = FM_PCD_AD_CONT_LOOKUP_TYPE;
    ccAdBaseReg |= (p_ManipParams->dontFragAction
            << FM_PCD_MANIP_IP_FRAG_DF_SHIFT);


    /* Set Scatter/Gather BPid */
    if (p_ManipParams->sgBpidEn)
    {
        ccAdBaseReg |= FM_PCD_MANIP_IP_FRAG_SG_BDID_EN;
        pcAndOffsetsReg |= ((p_ManipParams->sgBpid
                << FM_PCD_MANIP_IP_FRAG_SG_BDID_SHIFT)
                & FM_PCD_MANIP_IP_FRAG_SG_BDID_MASK);
    }

    /* Prepare the first Ad register (gmask) - scratch buffer pool id and Pointer to fragment ID */
    gmaskReg = (uint32_t)(XX_VirtToPhys(UINT_TO_PTR(p_FmPcd->ipv6FrameIdAddr))
            - p_FmPcd->physicalMuramBase);
#if (DPAA_VERSION == 10)
    gmaskReg |= p_ManipParams->scratchBpid << FM_PCD_MANIP_IP_FRAG_SCRATCH_BPID;
#else
    gmaskReg |= (0xFF) << FM_PCD_MANIP_IP_FRAG_SCRATCH_BPID;
#endif /* (DPAA_VERSION == 10) */

    /* Set all Ad registers */
    WRITE_UINT32(p_Manip->fragParams.p_Frag->pcAndOffsets, pcAndOffsetsReg);
    WRITE_UINT32(p_Manip->fragParams.p_Frag->ccAdBase, ccAdBaseReg);
    WRITE_UINT32(p_Manip->fragParams.p_Frag->gmask, gmaskReg);

    /* Saves user's fragmentation manipulation parameters */
    p_Manip->frag = TRUE;
    p_Manip->sizeForFragmentation = p_ManipParams->sizeForFragmentation;

#if (DPAA_VERSION == 10)
    p_Manip->fragParams.scratchBpid = p_ManipParams->scratchBpid;

    /* scratch buffer pool initialization */
    if ((err = FmPcdFragHcScratchPoolFill((t_Handle)p_FmPcd, p_ManipParams->scratchBpid)) != E_OK)
    {
        FM_MURAM_FreeMem(p_FmPcd->h_FmMuram, p_Manip->fragParams.p_Frag);
        p_Manip->fragParams.p_Frag = NULL;
        RETURN_ERROR(MAJOR, err, NO_MSG);
    }
#endif /* (DPAA_VERSION == 10) */

    return E_OK;
}