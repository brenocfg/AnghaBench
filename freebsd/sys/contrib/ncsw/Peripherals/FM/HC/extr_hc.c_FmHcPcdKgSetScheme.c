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
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  kgse_mv; int /*<<< orphan*/  kgse_ccbs; int /*<<< orphan*/  kgse_dv1; int /*<<< orphan*/  kgse_dv0; } ;
struct TYPE_7__ {TYPE_4__ schemeRegs; } ;
struct TYPE_8__ {void* commandSequence; TYPE_1__ hcSpecificData; int /*<<< orphan*/  extraReg; int /*<<< orphan*/  actionReg; void* opcode; } ;
typedef  TYPE_2__ t_HcFrame ;
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_FmHc ;
typedef  scalar_t__ t_Error ;
typedef  int /*<<< orphan*/  t_DpaaFD ;
struct fman_kg_scheme_regs {int /*<<< orphan*/  kgse_mv; int /*<<< orphan*/  kgse_ccbs; int /*<<< orphan*/  kgse_dv1; int /*<<< orphan*/  kgse_dv0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_FD (int) ; 
 scalar_t__ E_NO_MEMORY ; 
 scalar_t__ E_OK ; 
 scalar_t__ EnQFrm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  FmPcdKgBuildWriteSchemeActionReg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FmPcdKgGetSchemeId (scalar_t__) ; 
 TYPE_2__* GetBuf (int /*<<< orphan*/ *,void**) ; 
 int HC_HCOR_GBL ; 
 int /*<<< orphan*/  HC_HCOR_KG_SCHEME_REGS_MASK ; 
 int HC_HCOR_OPCODE_KG_SCM ; 
 int /*<<< orphan*/  MINOR ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  PutBuf (int /*<<< orphan*/ *,TYPE_2__*,void*) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,struct fman_kg_scheme_regs*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

t_Error FmHcPcdKgSetScheme(t_Handle                    h_FmHc,
                           t_Handle                    h_Scheme,
                           struct fman_kg_scheme_regs  *p_SchemeRegs,
                           bool                        updateCounter)
{
    t_FmHc                              *p_FmHc = (t_FmHc*)h_FmHc;
    t_Error                             err = E_OK;
    t_HcFrame                           *p_HcFrame;
    t_DpaaFD                            fmFd;
    uint8_t                             physicalSchemeId;
    uint32_t                            seqNum;

    p_HcFrame = GetBuf(p_FmHc, &seqNum);
    if (!p_HcFrame)
        RETURN_ERROR(MINOR, E_NO_MEMORY, ("HC Frame object"));

    physicalSchemeId = FmPcdKgGetSchemeId(h_Scheme);

    memset(p_HcFrame, 0, sizeof(t_HcFrame));
    p_HcFrame->opcode = (uint32_t)(HC_HCOR_GBL | HC_HCOR_OPCODE_KG_SCM);
    p_HcFrame->actionReg  = FmPcdKgBuildWriteSchemeActionReg(physicalSchemeId, updateCounter);
    p_HcFrame->extraReg = HC_HCOR_KG_SCHEME_REGS_MASK;
    memcpy(&p_HcFrame->hcSpecificData.schemeRegs, p_SchemeRegs, sizeof(struct fman_kg_scheme_regs));
    if (!updateCounter)
    {
        p_HcFrame->hcSpecificData.schemeRegs.kgse_dv0   = p_SchemeRegs->kgse_dv0;
        p_HcFrame->hcSpecificData.schemeRegs.kgse_dv1   = p_SchemeRegs->kgse_dv1;
        p_HcFrame->hcSpecificData.schemeRegs.kgse_ccbs  = p_SchemeRegs->kgse_ccbs;
        p_HcFrame->hcSpecificData.schemeRegs.kgse_mv    = p_SchemeRegs->kgse_mv;
    }
    p_HcFrame->commandSequence = seqNum;

    BUILD_FD(sizeof(t_HcFrame));

    err = EnQFrm(p_FmHc, &fmFd, seqNum);

    PutBuf(p_FmHc, p_HcFrame, seqNum);

    if (err != E_OK)
        RETURN_ERROR(MINOR, err, NO_MSG);

    return E_OK;
}