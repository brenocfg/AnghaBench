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
struct TYPE_6__ {int /*<<< orphan*/  ccCapwapReassmTimeout; } ;
struct TYPE_7__ {void* commandSequence; TYPE_1__ hcSpecificData; void* opcode; } ;
typedef  TYPE_2__ t_HcFrame ;
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_FmPcdCcCapwapReassmTimeoutParams ;
typedef  int /*<<< orphan*/  t_FmHc ;
typedef  int /*<<< orphan*/  t_Error ;
typedef  int /*<<< orphan*/  t_DpaaFD ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_FD (int) ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  EnQFrm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 TYPE_2__* GetBuf (int /*<<< orphan*/ *,void**) ; 
 int HC_HCOR_GBL ; 
 int HC_HCOR_OPCODE_CC_CAPWAP_REASSM_TIMEOUT ; 
 int /*<<< orphan*/  MINOR ; 
 int /*<<< orphan*/  PutBuf (int /*<<< orphan*/ *,TYPE_2__*,void*) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_VALUE (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

t_Error FmHcPcdCcCapwapTimeoutReassm(t_Handle h_FmHc, t_FmPcdCcCapwapReassmTimeoutParams *p_CcCapwapReassmTimeoutParams )
{
    t_FmHc                              *p_FmHc = (t_FmHc*)h_FmHc;
    t_HcFrame                           *p_HcFrame;
    t_DpaaFD                            fmFd;
    t_Error                             err;
    uint32_t                            seqNum;

    SANITY_CHECK_RETURN_VALUE(h_FmHc, E_INVALID_HANDLE,0);

    p_HcFrame = GetBuf(p_FmHc, &seqNum);
    if (!p_HcFrame)
        RETURN_ERROR(MINOR, E_NO_MEMORY, ("HC Frame object"));

    memset(p_HcFrame, 0, sizeof(t_HcFrame));
    p_HcFrame->opcode = (uint32_t)(HC_HCOR_GBL | HC_HCOR_OPCODE_CC_CAPWAP_REASSM_TIMEOUT);
    memcpy(&p_HcFrame->hcSpecificData.ccCapwapReassmTimeout, p_CcCapwapReassmTimeoutParams, sizeof(t_FmPcdCcCapwapReassmTimeoutParams));
    p_HcFrame->commandSequence = seqNum;
    BUILD_FD(sizeof(t_HcFrame));

    err = EnQFrm(p_FmHc, &fmFd, seqNum);

    PutBuf(p_FmHc, p_HcFrame, seqNum);
    return err;
}