#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  void* uint32_t ;
struct TYPE_10__ {void* singleRegForWrite; } ;
struct TYPE_11__ {void* commandSequence; TYPE_1__ hcSpecificData; int /*<<< orphan*/  extraReg; int /*<<< orphan*/  actionReg; void* opcode; } ;
typedef  TYPE_2__ t_HcFrame ;
typedef  scalar_t__ t_Handle ;
struct TYPE_12__ {int /*<<< orphan*/  h_FmPcd; } ;
typedef  TYPE_3__ t_FmHc ;
typedef  int /*<<< orphan*/  t_Error ;
typedef  int /*<<< orphan*/  t_DpaaFD ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_FD (int) ; 
 int /*<<< orphan*/  E_NOT_IN_RANGE ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  EnQFrm (TYPE_3__*,int /*<<< orphan*/ *,void*) ; 
 scalar_t__ FM_PCD_KG_NUM_OF_SCHEMES ; 
 int /*<<< orphan*/  FmPcdKgBuildWriteSchemeActionReg (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ FmPcdKgGetRelativeSchemeId (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ FmPcdKgGetSchemeId (scalar_t__) ; 
 TYPE_2__* GetBuf (TYPE_3__*,void**) ; 
 int HC_HCOR_GBL ; 
 int /*<<< orphan*/  HC_HCOR_KG_SCHEME_COUNTER ; 
 int HC_HCOR_OPCODE_KG_SCM ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MINOR ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  PutBuf (TYPE_3__*,TYPE_2__*,void*) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

t_Error  FmHcPcdKgSetSchemeCounter(t_Handle h_FmHc, t_Handle h_Scheme, uint32_t value)
{
    t_FmHc      *p_FmHc = (t_FmHc*)h_FmHc;
    t_Error     err = E_OK;
    t_HcFrame   *p_HcFrame;
    t_DpaaFD    fmFd;
    uint8_t     relativeSchemeId, physicalSchemeId;
    uint32_t    seqNum;

    physicalSchemeId = FmPcdKgGetSchemeId(h_Scheme);
    relativeSchemeId = FmPcdKgGetRelativeSchemeId(p_FmHc->h_FmPcd, physicalSchemeId);
    if ( relativeSchemeId == FM_PCD_KG_NUM_OF_SCHEMES)
        RETURN_ERROR(MAJOR, E_NOT_IN_RANGE, NO_MSG);

    /* first read scheme and check that it is valid */
    p_HcFrame = GetBuf(p_FmHc, &seqNum);
    if (!p_HcFrame)
        RETURN_ERROR(MINOR, E_NO_MEMORY, ("HC Frame object"));
    memset(p_HcFrame, 0, sizeof(t_HcFrame));
    p_HcFrame->opcode = (uint32_t)(HC_HCOR_GBL | HC_HCOR_OPCODE_KG_SCM);
    p_HcFrame->actionReg  = FmPcdKgBuildWriteSchemeActionReg(physicalSchemeId, TRUE);
    p_HcFrame->extraReg = HC_HCOR_KG_SCHEME_COUNTER;
    /* write counter */
    p_HcFrame->hcSpecificData.singleRegForWrite = value;
    p_HcFrame->commandSequence = seqNum;

    BUILD_FD(sizeof(t_HcFrame));

    err = EnQFrm(p_FmHc, &fmFd, seqNum);

    PutBuf(p_FmHc, p_HcFrame, seqNum);
    return err;
}