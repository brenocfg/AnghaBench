#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_7__ {void* fmpl_perrpc; void* fmpl_perypc; void* fmpl_perpc; void* fmpl_peypc; void* fmpl_pegpc; } ;
struct TYPE_8__ {TYPE_1__ profileRegs; } ;
struct TYPE_9__ {int extraReg; TYPE_2__ hcSpecificData; void* commandSequence; int /*<<< orphan*/  actionReg; void* opcode; } ;
typedef  TYPE_3__ t_HcFrame ;
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_FmHc ;
typedef  scalar_t__ t_Error ;
typedef  int /*<<< orphan*/  t_DpaaFD ;
typedef  int e_FmPcdPlcrProfileCounters ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_FD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 scalar_t__ E_INVALID_SELECTION ; 
 scalar_t__ E_NO_MEMORY ; 
 scalar_t__ E_OK ; 
 scalar_t__ EnQFrm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  FmPcdPlcrBuildReadPlcrActionReg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdPlcrProfileGetAbsoluteId (scalar_t__) ; 
 TYPE_3__* GetBuf (int /*<<< orphan*/ *,void**) ; 
 int HC_HCOR_GBL ; 
 int HC_HCOR_OPCODE_PLCR_PRFL ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MINOR ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  PutBuf (int /*<<< orphan*/ *,TYPE_3__*,void*) ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_VALUE (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIZE_OF_HC_FRAME_READ_OR_CC_DYNAMIC ; 
#define  e_FM_PCD_PLCR_PROFILE_GREEN_PACKET_TOTAL_COUNTER 132 
#define  e_FM_PCD_PLCR_PROFILE_RECOLOURED_RED_PACKET_TOTAL_COUNTER 131 
#define  e_FM_PCD_PLCR_PROFILE_RECOLOURED_YELLOW_PACKET_TOTAL_COUNTER 130 
#define  e_FM_PCD_PLCR_PROFILE_RED_PACKET_TOTAL_COUNTER 129 
#define  e_FM_PCD_PLCR_PROFILE_YELLOW_PACKET_TOTAL_COUNTER 128 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

uint32_t FmHcPcdPlcrGetProfileCounter(t_Handle h_FmHc, t_Handle h_Profile, e_FmPcdPlcrProfileCounters counter)
{
    t_FmHc      *p_FmHc = (t_FmHc*)h_FmHc;
    uint16_t    absoluteProfileId = FmPcdPlcrProfileGetAbsoluteId(h_Profile);
    t_Error     err;
    t_HcFrame   *p_HcFrame;
    t_DpaaFD    fmFd;
    uint32_t    retVal = 0;
    uint32_t    seqNum;

    SANITY_CHECK_RETURN_VALUE(h_FmHc, E_INVALID_HANDLE,0);

    /* first read scheme and check that it is valid */
    p_HcFrame = GetBuf(p_FmHc, &seqNum);
    if (!p_HcFrame)
    {
        REPORT_ERROR(MINOR, E_NO_MEMORY, ("HC Frame object"));
        return 0;
    }
    memset(p_HcFrame, 0, sizeof(t_HcFrame));
    p_HcFrame->opcode = (uint32_t)(HC_HCOR_GBL | HC_HCOR_OPCODE_PLCR_PRFL);
    p_HcFrame->actionReg  = FmPcdPlcrBuildReadPlcrActionReg(absoluteProfileId);
    p_HcFrame->extraReg = 0x00008000;
    p_HcFrame->commandSequence = seqNum;

    BUILD_FD(SIZE_OF_HC_FRAME_READ_OR_CC_DYNAMIC);

    err = EnQFrm(p_FmHc, &fmFd, seqNum);
    if (err != E_OK)
    {
        PutBuf(p_FmHc, p_HcFrame, seqNum);
        REPORT_ERROR(MINOR, err, NO_MSG);
        return 0;
    }

    switch (counter)
    {
        case e_FM_PCD_PLCR_PROFILE_GREEN_PACKET_TOTAL_COUNTER:
            retVal = p_HcFrame->hcSpecificData.profileRegs.fmpl_pegpc;
            break;
        case e_FM_PCD_PLCR_PROFILE_YELLOW_PACKET_TOTAL_COUNTER:
            retVal = p_HcFrame->hcSpecificData.profileRegs.fmpl_peypc;
            break;
        case e_FM_PCD_PLCR_PROFILE_RED_PACKET_TOTAL_COUNTER:
            retVal = p_HcFrame->hcSpecificData.profileRegs.fmpl_perpc;
            break;
        case e_FM_PCD_PLCR_PROFILE_RECOLOURED_YELLOW_PACKET_TOTAL_COUNTER:
            retVal = p_HcFrame->hcSpecificData.profileRegs.fmpl_perypc;
            break;
        case e_FM_PCD_PLCR_PROFILE_RECOLOURED_RED_PACKET_TOTAL_COUNTER:
            retVal = p_HcFrame->hcSpecificData.profileRegs.fmpl_perrpc;
            break;
        default:
            REPORT_ERROR(MAJOR, E_INVALID_SELECTION, NO_MSG);
    }

    PutBuf(p_FmHc, p_HcFrame, seqNum);
    return retVal;
}