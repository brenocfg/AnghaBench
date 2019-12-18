#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {void* singleRegForWrite; } ;
struct TYPE_7__ {int extraReg; void* commandSequence; TYPE_1__ hcSpecificData; int /*<<< orphan*/  actionReg; void* opcode; } ;
typedef  TYPE_2__ t_HcFrame ;
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_FmHc ;
typedef  scalar_t__ t_Error ;
typedef  int /*<<< orphan*/  t_DpaaFD ;
typedef  int /*<<< orphan*/  e_FmPcdPlcrProfileCounters ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_FD (int /*<<< orphan*/ ) ; 
 scalar_t__ E_NO_MEMORY ; 
 scalar_t__ E_OK ; 
 scalar_t__ EnQFrm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  FmPcdPlcrBuildCounterProfileReg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdPlcrBuildWritePlcrActionReg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdPlcrProfileGetAbsoluteId (scalar_t__) ; 
 TYPE_2__* GetBuf (int /*<<< orphan*/ *,void**) ; 
 int HC_HCOR_GBL ; 
 int HC_HCOR_OPCODE_PLCR_PRFL ; 
 int /*<<< orphan*/  MINOR ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  PutBuf (int /*<<< orphan*/ *,TYPE_2__*,void*) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  SIZE_OF_HC_FRAME_PROFILE_CNT ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

t_Error  FmHcPcdPlcrSetProfileCounter(t_Handle h_FmHc, t_Handle h_Profile, e_FmPcdPlcrProfileCounters counter, uint32_t value)
{

    t_FmHc      *p_FmHc = (t_FmHc*)h_FmHc;
    uint16_t    absoluteProfileId = FmPcdPlcrProfileGetAbsoluteId(h_Profile);
    t_Error     err = E_OK;
    t_HcFrame   *p_HcFrame;
    t_DpaaFD    fmFd;
    uint32_t    seqNum;

    /* first read scheme and check that it is valid */
    p_HcFrame = GetBuf(p_FmHc, &seqNum);
    if (!p_HcFrame)
        RETURN_ERROR(MINOR, E_NO_MEMORY, ("HC Frame object"));
    memset(p_HcFrame, 0, sizeof(t_HcFrame));
    p_HcFrame->opcode = (uint32_t)(HC_HCOR_GBL | HC_HCOR_OPCODE_PLCR_PRFL);
    p_HcFrame->actionReg  = FmPcdPlcrBuildWritePlcrActionReg(absoluteProfileId);
    p_HcFrame->actionReg |= FmPcdPlcrBuildCounterProfileReg(counter);
    p_HcFrame->extraReg = 0x00008000;
    p_HcFrame->hcSpecificData.singleRegForWrite = value;
    p_HcFrame->commandSequence = seqNum;

    BUILD_FD(SIZE_OF_HC_FRAME_PROFILE_CNT);

    err = EnQFrm(p_FmHc, &fmFd, seqNum);

    PutBuf(p_FmHc, p_HcFrame, seqNum);

    if (err != E_OK)
        RETURN_ERROR(MINOR, err, NO_MSG);

    return E_OK;
}