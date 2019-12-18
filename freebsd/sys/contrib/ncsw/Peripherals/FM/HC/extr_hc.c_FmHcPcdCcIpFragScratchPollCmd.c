#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_7__ {int actionReg; int /*<<< orphan*/  extraReg; void* commandSequence; void* opcode; } ;
typedef  TYPE_1__ t_HcFrame ;
typedef  scalar_t__ t_Handle ;
struct TYPE_8__ {int bufferPoolId; int /*<<< orphan*/  numOfBuffers; } ;
typedef  TYPE_2__ t_FmPcdCcFragScratchPoolCmdParams ;
typedef  int /*<<< orphan*/  t_FmHc ;
typedef  int /*<<< orphan*/  t_Error ;
typedef  int /*<<< orphan*/  t_DpaaFD ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_FD (int) ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  EnQFrm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 TYPE_1__* GetBuf (int /*<<< orphan*/ *,void**) ; 
 int HC_HCOR_ACTION_REG_IP_FRAG_SCRATCH_POOL_BPID ; 
 int HC_HCOR_ACTION_REG_IP_FRAG_SCRATCH_POOL_CMD_SHIFT ; 
 int HC_HCOR_GBL ; 
 int HC_HCOR_OPCODE_CC_IP_FRAG_INITIALIZATION ; 
 int /*<<< orphan*/  MINOR ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  PutBuf (int /*<<< orphan*/ *,TYPE_1__*,void*) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_VALUE (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

t_Error FmHcPcdCcIpFragScratchPollCmd(t_Handle h_FmHc, bool fill, t_FmPcdCcFragScratchPoolCmdParams *p_FmPcdCcFragScratchPoolCmdParams)
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

    p_HcFrame->opcode     = (uint32_t)(HC_HCOR_GBL | HC_HCOR_OPCODE_CC_IP_FRAG_INITIALIZATION);
    p_HcFrame->actionReg  = (uint32_t)(((fill == TRUE) ? 0 : 1) << HC_HCOR_ACTION_REG_IP_FRAG_SCRATCH_POOL_CMD_SHIFT);
    p_HcFrame->actionReg |= p_FmPcdCcFragScratchPoolCmdParams->bufferPoolId << HC_HCOR_ACTION_REG_IP_FRAG_SCRATCH_POOL_BPID;
    if (fill == TRUE)
    {
        p_HcFrame->extraReg   = p_FmPcdCcFragScratchPoolCmdParams->numOfBuffers;
    }
    p_HcFrame->commandSequence = seqNum;

    BUILD_FD(sizeof(t_HcFrame));
    if ((err = EnQFrm(p_FmHc, &fmFd, seqNum)) != E_OK)
    {
        PutBuf(p_FmHc, p_HcFrame, seqNum);
        RETURN_ERROR(MINOR, err, NO_MSG);
    }

    p_FmPcdCcFragScratchPoolCmdParams->numOfBuffers = p_HcFrame->extraReg;

    PutBuf(p_FmHc, p_HcFrame, seqNum);
    return E_OK;
}