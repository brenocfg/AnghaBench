#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * t_Handle ;
struct TYPE_16__ {int /*<<< orphan*/  p_AdTableNew; int /*<<< orphan*/  p_KeysMatchTableNew; int /*<<< orphan*/  numOfKeys; } ;
typedef  TYPE_4__ t_FmPcdModifyCcKeyAdditionalParams ;
struct TYPE_17__ {int /*<<< orphan*/  h_FmPcd; int /*<<< orphan*/ * h_Ad; int /*<<< orphan*/  p_GlblMask; int /*<<< orphan*/  glblMaskSize; int /*<<< orphan*/  sizeOfExtraction; int /*<<< orphan*/  ccKeySizeAccExtraction; int /*<<< orphan*/  ctrlFlow; int /*<<< orphan*/  prsArrayOffset; int /*<<< orphan*/  offset; int /*<<< orphan*/  parseCode; int /*<<< orphan*/  lclMask; int /*<<< orphan*/  h_AdTable; int /*<<< orphan*/  h_KeysMatchTable; int /*<<< orphan*/  numOfKeys; } ;
typedef  TYPE_5__ t_FmPcdCcNode ;
struct TYPE_14__ {int /*<<< orphan*/ * h_FrmReplic; } ;
struct TYPE_13__ {int /*<<< orphan*/  h_CcNode; } ;
struct TYPE_15__ {TYPE_2__ frParams; TYPE_1__ ccParams; } ;
struct TYPE_18__ {scalar_t__ nextEngine; TYPE_3__ params; int /*<<< orphan*/ * h_Manip; } ;
typedef  TYPE_6__ t_FmPcdCcNextEngineParams ;

/* Variables and functions */
 scalar_t__ AllocAndFillAdForContLookupManip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  FillAdOfTypeContLookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAJOR ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XX_Free (TYPE_5__*) ; 
 scalar_t__ XX_Malloc (int) ; 
 scalar_t__ e_FM_PCD_CC ; 
 scalar_t__ e_FM_PCD_FR ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static t_Handle BuildNewAd(
        t_Handle h_Ad,
        t_FmPcdModifyCcKeyAdditionalParams *p_FmPcdModifyCcKeyAdditionalParams,
        t_FmPcdCcNode *p_CcNode,
        t_FmPcdCcNextEngineParams *p_FmPcdCcNextEngineParams)
{
    t_FmPcdCcNode *p_FmPcdCcNodeTmp;
    t_Handle h_OrigAd = NULL;

    p_FmPcdCcNodeTmp = (t_FmPcdCcNode*)XX_Malloc(sizeof(t_FmPcdCcNode));
    if (!p_FmPcdCcNodeTmp)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("p_FmPcdCcNodeTmp"));
        return NULL;
    }
    memset(p_FmPcdCcNodeTmp, 0, sizeof(t_FmPcdCcNode));

    p_FmPcdCcNodeTmp->numOfKeys = p_FmPcdModifyCcKeyAdditionalParams->numOfKeys;
    p_FmPcdCcNodeTmp->h_KeysMatchTable =
            p_FmPcdModifyCcKeyAdditionalParams->p_KeysMatchTableNew;
    p_FmPcdCcNodeTmp->h_AdTable =
            p_FmPcdModifyCcKeyAdditionalParams->p_AdTableNew;

    p_FmPcdCcNodeTmp->lclMask = p_CcNode->lclMask;
    p_FmPcdCcNodeTmp->parseCode = p_CcNode->parseCode;
    p_FmPcdCcNodeTmp->offset = p_CcNode->offset;
    p_FmPcdCcNodeTmp->prsArrayOffset = p_CcNode->prsArrayOffset;
    p_FmPcdCcNodeTmp->ctrlFlow = p_CcNode->ctrlFlow;
    p_FmPcdCcNodeTmp->ccKeySizeAccExtraction = p_CcNode->ccKeySizeAccExtraction;
    p_FmPcdCcNodeTmp->sizeOfExtraction = p_CcNode->sizeOfExtraction;
    p_FmPcdCcNodeTmp->glblMaskSize = p_CcNode->glblMaskSize;
    p_FmPcdCcNodeTmp->p_GlblMask = p_CcNode->p_GlblMask;

    if (p_FmPcdCcNextEngineParams->nextEngine == e_FM_PCD_CC)
    {
        if (p_FmPcdCcNextEngineParams->h_Manip)
        {
            h_OrigAd = p_CcNode->h_Ad;
            if (AllocAndFillAdForContLookupManip(
                    p_FmPcdCcNextEngineParams->params.ccParams.h_CcNode)
                    != E_OK)
            {
                REPORT_ERROR(MAJOR, E_INVALID_STATE, NO_MSG);
                XX_Free(p_FmPcdCcNodeTmp);
                return NULL;
            }
        }
        FillAdOfTypeContLookup(h_Ad, NULL, p_CcNode->h_FmPcd, p_FmPcdCcNodeTmp,
                               h_OrigAd ? NULL : p_FmPcdCcNextEngineParams->h_Manip, NULL);
    }

#if (DPAA_VERSION >= 11)
    if ((p_FmPcdCcNextEngineParams->nextEngine == e_FM_PCD_FR)
            && (p_FmPcdCcNextEngineParams->params.frParams.h_FrmReplic))
    {
        FillAdOfTypeContLookup(
                h_Ad, NULL, p_CcNode->h_FmPcd, p_FmPcdCcNodeTmp,
                p_FmPcdCcNextEngineParams->h_Manip,
                p_FmPcdCcNextEngineParams->params.frParams.h_FrmReplic);
    }
#endif /* (DPAA_VERSION >= 11) */

    XX_Free(p_FmPcdCcNodeTmp);

    return NULL;
}