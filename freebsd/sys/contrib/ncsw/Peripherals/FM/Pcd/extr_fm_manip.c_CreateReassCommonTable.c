#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_14__ {int /*<<< orphan*/  expirationDelay; int /*<<< orphan*/  timeOutTblPtr; int /*<<< orphan*/  reassFrmDescPoolPtrLow; int /*<<< orphan*/  liodnAndReassFrmDescPoolPtrHi; int /*<<< orphan*/  reassFrmDescIndexPoolTblPtr; int /*<<< orphan*/  timeoutModeAndFqid; } ;
typedef  TYPE_2__ t_ReassCommonTbl ;
struct TYPE_13__ {scalar_t__ timeOutMode; int fqidForTimeOutFrames; int maxNumFramesInProcess; int dataLiodnOffset; int timeoutThresholdForReassmProcess; TYPE_2__* p_ReassCommonTbl; void* timeOutTblAddr; void* reassFrmDescrPoolTblAddr; int /*<<< orphan*/  dataMemId; void* reassFrmDescrIndxPoolTblAddr; } ;
struct TYPE_15__ {TYPE_1__ reassmParams; scalar_t__ h_FmPcd; } ;
typedef  TYPE_3__ t_FmPcdManip ;
struct TYPE_16__ {int /*<<< orphan*/  h_FmMuram; scalar_t__ physicalMuramBase; int /*<<< orphan*/  h_Fm; } ;
typedef  TYPE_4__ t_FmPcd ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 scalar_t__ E_NOT_AVAILABLE ; 
 scalar_t__ E_NO_MEMORY ; 
 scalar_t__ E_OK ; 
 scalar_t__ FM_MURAM_AllocMem (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  FM_MURAM_FreeMem (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int FM_PCD_MANIP_REASM_COMMON_PARAM_TABLE_ALIGN ; 
 int FM_PCD_MANIP_REASM_COMMON_PARAM_TABLE_SIZE ; 
 int FM_PCD_MANIP_REASM_ELIODN_MASK ; 
 scalar_t__ FM_PCD_MANIP_REASM_ELIODN_SHIFT ; 
 int FM_PCD_MANIP_REASM_LIODN_MASK ; 
 scalar_t__ FM_PCD_MANIP_REASM_LIODN_SHIFT ; 
 int FM_PCD_MANIP_REASM_TIME_OUT_BETWEEN_FRAMES ; 
 int FmGetTimeStampScale (int /*<<< orphan*/ ) ; 
 scalar_t__ FmPcdRegisterReassmPort (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MemSet8 (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ PTR_MOVE (TYPE_2__*,int) ; 
 void* PTR_TO_UINT (scalar_t__) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 TYPE_2__* UINT_TO_PTR (void*) ; 
 int /*<<< orphan*/  WRITE_UINT16 (int,int) ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ XX_MallocSmart (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ XX_VirtToPhys (TYPE_2__*) ; 
 scalar_t__ e_FM_PCD_MANIP_TIME_OUT_BETWEEN_FRAMES ; 

__attribute__((used)) static t_Error CreateReassCommonTable(t_FmPcdManip *p_Manip)
{
    uint32_t tmpReg32 = 0, i, bitFor1Micro;
    uint64_t tmpReg64, size;
    t_FmPcd *p_FmPcd = (t_FmPcd *)p_Manip->h_FmPcd;
    t_Error err = E_OK;

    bitFor1Micro = FmGetTimeStampScale(p_FmPcd->h_Fm);
    if (bitFor1Micro == 0)
        RETURN_ERROR(MAJOR, E_NOT_AVAILABLE, ("Timestamp scale"));

    /* Allocation of the Reassembly Common Parameters table. This table is located in the
     MURAM. Its size is 64 bytes and its base address should be 8-byte aligned. */
    p_Manip->reassmParams.p_ReassCommonTbl =
            (t_ReassCommonTbl *)FM_MURAM_AllocMem(
                    p_FmPcd->h_FmMuram,
                    FM_PCD_MANIP_REASM_COMMON_PARAM_TABLE_SIZE,
                    FM_PCD_MANIP_REASM_COMMON_PARAM_TABLE_ALIGN);

    if (!p_Manip->reassmParams.p_ReassCommonTbl)
        RETURN_ERROR(MAJOR, E_NO_MEMORY,
                     ("MURAM alloc for Reassembly common parameters table"));

    MemSet8(p_Manip->reassmParams.p_ReassCommonTbl, 0,
               FM_PCD_MANIP_REASM_COMMON_PARAM_TABLE_SIZE);

    /* Setting the TimeOut Mode.*/
    tmpReg32 = 0;
    if (p_Manip->reassmParams.timeOutMode
            == e_FM_PCD_MANIP_TIME_OUT_BETWEEN_FRAMES)
        tmpReg32 |= FM_PCD_MANIP_REASM_TIME_OUT_BETWEEN_FRAMES;

    /* Setting TimeOut FQID - Frames that time out are enqueued to this FQID.
     In order to cause TimeOut frames to be discarded, this queue should be configured accordingly*/
    tmpReg32 |= p_Manip->reassmParams.fqidForTimeOutFrames;
    WRITE_UINT32(p_Manip->reassmParams.p_ReassCommonTbl->timeoutModeAndFqid,
                 tmpReg32);

    /* Calculation the size of IP Reassembly Frame Descriptor - number of frames that are allowed to be reassembled simultaneously + 129.*/
    size = p_Manip->reassmParams.maxNumFramesInProcess + 129;

    /*Allocation of IP Reassembly Frame Descriptor Indexes Pool - This pool resides in the MURAM */
    p_Manip->reassmParams.reassFrmDescrIndxPoolTblAddr =
            PTR_TO_UINT(FM_MURAM_AllocMem(p_FmPcd->h_FmMuram,
                            (uint32_t)(size * 2),
                            256));
    if (!p_Manip->reassmParams.reassFrmDescrIndxPoolTblAddr)
        RETURN_ERROR(
                MAJOR, E_NO_MEMORY,
                ("MURAM alloc for Reassembly frame descriptor indexes pool"));

    MemSet8(UINT_TO_PTR(p_Manip->reassmParams.reassFrmDescrIndxPoolTblAddr),
               0, (uint32_t)(size * 2));

    /* The entries in IP Reassembly Frame Descriptor Indexes Pool contains indexes starting with 1 up to
     the maximum number of frames that are allowed to be reassembled simultaneously + 128.
     The last entry in this pool must contain the index zero*/
    for (i = 0; i < (size - 1); i++)
        WRITE_UINT16(
                *(uint16_t *)PTR_MOVE(UINT_TO_PTR(p_Manip->reassmParams.reassFrmDescrIndxPoolTblAddr), (i<<1)),
                (uint16_t)(i+1));

    /* Sets the IP Reassembly Frame Descriptor Indexes Pool offset from MURAM */
    tmpReg32 = (uint32_t)(XX_VirtToPhys(
            UINT_TO_PTR(p_Manip->reassmParams.reassFrmDescrIndxPoolTblAddr))
            - p_FmPcd->physicalMuramBase);
    WRITE_UINT32(
            p_Manip->reassmParams.p_ReassCommonTbl->reassFrmDescIndexPoolTblPtr,
            tmpReg32);

    /* Allocation of the Reassembly Frame Descriptors Pool - This pool resides in external memory.
     The number of entries in this pool should be equal to the number of entries in IP Reassembly Frame Descriptor Indexes Pool.*/
    p_Manip->reassmParams.reassFrmDescrPoolTblAddr =
            PTR_TO_UINT(XX_MallocSmart((uint32_t)(size * 64), p_Manip->reassmParams.dataMemId, 64));

    if (!p_Manip->reassmParams.reassFrmDescrPoolTblAddr)
        RETURN_ERROR(MAJOR, E_NO_MEMORY, ("Memory allocation FAILED"));

    MemSet8(UINT_TO_PTR(p_Manip->reassmParams.reassFrmDescrPoolTblAddr), 0,
               (uint32_t)(size * 64));

    /* Sets the Reassembly Frame Descriptors Pool and liodn offset*/
    tmpReg64 = (uint64_t)(XX_VirtToPhys(
            UINT_TO_PTR(p_Manip->reassmParams.reassFrmDescrPoolTblAddr)));
    tmpReg64 |= ((uint64_t)(p_Manip->reassmParams.dataLiodnOffset
            & FM_PCD_MANIP_REASM_LIODN_MASK)
            << (uint64_t)FM_PCD_MANIP_REASM_LIODN_SHIFT);
    tmpReg64 |= ((uint64_t)(p_Manip->reassmParams.dataLiodnOffset
            & FM_PCD_MANIP_REASM_ELIODN_MASK)
            << (uint64_t)FM_PCD_MANIP_REASM_ELIODN_SHIFT);
    WRITE_UINT32(
            p_Manip->reassmParams.p_ReassCommonTbl->liodnAndReassFrmDescPoolPtrHi,
            (uint32_t)(tmpReg64 >> 32));
    WRITE_UINT32(
            p_Manip->reassmParams.p_ReassCommonTbl->reassFrmDescPoolPtrLow,
            (uint32_t)tmpReg64);

    /*Allocation of the TimeOut table - This table resides in the MURAM.
     The number of entries in this table is identical to the number of entries in the Reassembly Frame Descriptors Pool*/
    p_Manip->reassmParams.timeOutTblAddr =
            PTR_TO_UINT(FM_MURAM_AllocMem(p_FmPcd->h_FmMuram, (uint32_t)(size * 8),8));

    if (!p_Manip->reassmParams.timeOutTblAddr)
        RETURN_ERROR(MAJOR, E_NO_MEMORY,
                     ("MURAM alloc for Reassembly timeout table"));

    MemSet8(UINT_TO_PTR(p_Manip->reassmParams.timeOutTblAddr), 0,
               (uint16_t)(size * 8));

    /* Sets the TimeOut table offset from MURAM */
    tmpReg32 = (uint32_t)(XX_VirtToPhys(
            UINT_TO_PTR(p_Manip->reassmParams.timeOutTblAddr))
            - p_FmPcd->physicalMuramBase);
    WRITE_UINT32(p_Manip->reassmParams.p_ReassCommonTbl->timeOutTblPtr,
                 tmpReg32);

    /* Sets the Expiration Delay */
    tmpReg32 = 0;
    tmpReg32 |= (((uint32_t)(1 << bitFor1Micro))
            * p_Manip->reassmParams.timeoutThresholdForReassmProcess);
    WRITE_UINT32(p_Manip->reassmParams.p_ReassCommonTbl->expirationDelay,
                 tmpReg32);

    err = FmPcdRegisterReassmPort(p_FmPcd,
                                  p_Manip->reassmParams.p_ReassCommonTbl);
    if (err != E_OK)
    {
        FM_MURAM_FreeMem(p_FmPcd->h_FmMuram,
                         p_Manip->reassmParams.p_ReassCommonTbl);
        RETURN_ERROR(MAJOR, err, ("port registration"));
    }

    return err;
}