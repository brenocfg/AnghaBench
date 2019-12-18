#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  void* uint32_t ;
struct TYPE_11__ {void* kgse_spc; int /*<<< orphan*/  kgse_mode; } ;
struct TYPE_12__ {TYPE_1__ schemeRegs; } ;
struct TYPE_13__ {TYPE_2__ hcSpecificData; void* commandSequence; int /*<<< orphan*/  extraReg; int /*<<< orphan*/  actionReg; void* opcode; } ;
typedef  TYPE_3__ t_HcFrame ;
typedef  scalar_t__ t_Handle ;
struct TYPE_14__ {int /*<<< orphan*/  h_FmPcd; } ;
typedef  TYPE_4__ t_FmHc ;
typedef  scalar_t__ t_Error ;
typedef  int /*<<< orphan*/  t_DpaaFD ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_FD (int /*<<< orphan*/ ) ; 
 scalar_t__ E_ALREADY_EXISTS ; 
 scalar_t__ E_NOT_IN_RANGE ; 
 scalar_t__ E_NO_MEMORY ; 
 scalar_t__ E_OK ; 
 scalar_t__ EnQFrm (TYPE_4__*,int /*<<< orphan*/ *,void*) ; 
 scalar_t__ FM_PCD_KG_NUM_OF_SCHEMES ; 
 int /*<<< orphan*/  FmPcdKgBuildReadSchemeActionReg (scalar_t__) ; 
 scalar_t__ FmPcdKgGetRelativeSchemeId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ FmPcdKgGetSchemeId (scalar_t__) ; 
 int /*<<< orphan*/  FmPcdKgHwSchemeIsValid (int /*<<< orphan*/ ) ; 
 TYPE_3__* GetBuf (TYPE_4__*,void**) ; 
 int HC_HCOR_GBL ; 
 int /*<<< orphan*/  HC_HCOR_KG_SCHEME_REGS_MASK ; 
 int HC_HCOR_OPCODE_KG_SCM ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MINOR ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  PutBuf (TYPE_4__*,TYPE_3__*,void*) ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  SIZE_OF_HC_FRAME_READ_OR_CC_DYNAMIC ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

uint32_t  FmHcPcdKgGetSchemeCounter(t_Handle h_FmHc, t_Handle h_Scheme)
{
    t_FmHc      *p_FmHc = (t_FmHc*)h_FmHc;
    t_Error     err;
    t_HcFrame   *p_HcFrame;
    t_DpaaFD    fmFd;
    uint32_t    retVal;
    uint8_t     relativeSchemeId;
    uint8_t     physicalSchemeId = FmPcdKgGetSchemeId(h_Scheme);
    uint32_t    seqNum;

    relativeSchemeId = FmPcdKgGetRelativeSchemeId(p_FmHc->h_FmPcd, physicalSchemeId);
    if ( relativeSchemeId == FM_PCD_KG_NUM_OF_SCHEMES)
    {
        REPORT_ERROR(MAJOR, E_NOT_IN_RANGE, NO_MSG);
        return 0;
    }

    /* first read scheme and check that it is valid */
    p_HcFrame = GetBuf(p_FmHc, &seqNum);
    if (!p_HcFrame)
    {
        REPORT_ERROR(MINOR, E_NO_MEMORY, ("HC Frame object"));
        return 0;
    }
    memset(p_HcFrame, 0, sizeof(t_HcFrame));
    p_HcFrame->opcode = (uint32_t)(HC_HCOR_GBL | HC_HCOR_OPCODE_KG_SCM);
    p_HcFrame->actionReg  = FmPcdKgBuildReadSchemeActionReg(physicalSchemeId);
    p_HcFrame->extraReg = HC_HCOR_KG_SCHEME_REGS_MASK;
    p_HcFrame->commandSequence = seqNum;

    BUILD_FD(SIZE_OF_HC_FRAME_READ_OR_CC_DYNAMIC);

    err = EnQFrm(p_FmHc, &fmFd, seqNum);
    if (err != E_OK)
    {
        PutBuf(p_FmHc, p_HcFrame, seqNum);
        REPORT_ERROR(MINOR, err, NO_MSG);
        return 0;
    }

    if (!FmPcdKgHwSchemeIsValid(p_HcFrame->hcSpecificData.schemeRegs.kgse_mode))
    {
        PutBuf(p_FmHc, p_HcFrame, seqNum);
        REPORT_ERROR(MAJOR, E_ALREADY_EXISTS, ("Scheme is invalid"));
        return 0;
    }

    retVal = p_HcFrame->hcSpecificData.schemeRegs.kgse_spc;
    PutBuf(p_FmHc, p_HcFrame, seqNum);

    return retVal;
}