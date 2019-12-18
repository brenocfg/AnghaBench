#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  t_Handle ;
struct TYPE_16__ {int numOfUsedExtracts; int privateDflt0; int privateDflt1; int numOfUsedDflts; TYPE_6__* dflts; TYPE_5__* extractArray; } ;
struct TYPE_11__ {scalar_t__ grpId; int /*<<< orphan*/  h_CcTree; } ;
struct TYPE_12__ {TYPE_2__ cc; } ;
struct TYPE_10__ {int numOfDistinctionUnits; scalar_t__* unitIds; int /*<<< orphan*/  h_NetEnv; } ;
struct TYPE_17__ {TYPE_7__ keyExtractAndHashParams; int /*<<< orphan*/  useHash; TYPE_3__ kgNextEngineParams; int /*<<< orphan*/  nextEngine; TYPE_1__ netEnvParams; } ;
typedef  TYPE_8__ t_FmPcdKgSchemeParams ;
typedef  int /*<<< orphan*/  t_FmPcd ;
struct TYPE_15__ {int /*<<< orphan*/  dfltSelect; int /*<<< orphan*/  type; } ;
struct TYPE_13__ {int offset; int size; void* action; int /*<<< orphan*/  src; } ;
struct TYPE_14__ {TYPE_4__ extractNonHdr; void* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FM_PCD_MAX_NUM_OF_DISTINCTION_UNITS ; 
 int /*<<< orphan*/  FmPcdGetNetEnvId (int /*<<< orphan*/ ) ; 
 scalar_t__ FmPcdNetEnvGetUnitId (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEADER_TYPE_USER_DEFINED_SHIM2 ; 
 int /*<<< orphan*/  TRUE ; 
 void* e_FM_PCD_ACTION_NONE ; 
 int /*<<< orphan*/  e_FM_PCD_CC ; 
 int /*<<< orphan*/  e_FM_PCD_EXTRACT_FROM_DFLT_VALUE ; 
 int /*<<< orphan*/  e_FM_PCD_EXTRACT_FROM_PARSE_RESULT ; 
 void* e_FM_PCD_EXTRACT_NON_HDR ; 
 int /*<<< orphan*/  e_FM_PCD_KG_DFLT_PRIVATE_0 ; 
 int /*<<< orphan*/  e_FM_PCD_KG_GENERIC_NOT_FROM_DATA ; 

__attribute__((used)) static void setCapwapReassmSchemeParams(t_FmPcd* p_FmPcd,
                                        t_FmPcdKgSchemeParams *p_Scheme,
                                        t_Handle h_CcTree, uint8_t groupId)
{
    uint8_t res;

    /* Configures scheme's network environment parameters */
    p_Scheme->netEnvParams.numOfDistinctionUnits = 1;
    res = FmPcdNetEnvGetUnitId(
            p_FmPcd, FmPcdGetNetEnvId(p_Scheme->netEnvParams.h_NetEnv),
            HEADER_TYPE_USER_DEFINED_SHIM2, FALSE, 0);
    ASSERT_COND(res != FM_PCD_MAX_NUM_OF_DISTINCTION_UNITS);
    p_Scheme->netEnvParams.unitIds[0] = res;

    /* Configures scheme's next engine parameters*/
    p_Scheme->nextEngine = e_FM_PCD_CC;
    p_Scheme->kgNextEngineParams.cc.h_CcTree = h_CcTree;
    p_Scheme->kgNextEngineParams.cc.grpId = groupId;
    p_Scheme->useHash = TRUE;

    /* Configures scheme's key*/
    p_Scheme->keyExtractAndHashParams.numOfUsedExtracts = 2;
    p_Scheme->keyExtractAndHashParams.extractArray[0].type =
            e_FM_PCD_EXTRACT_NON_HDR;
    p_Scheme->keyExtractAndHashParams.extractArray[0].extractNonHdr.src =
            e_FM_PCD_EXTRACT_FROM_PARSE_RESULT;
    p_Scheme->keyExtractAndHashParams.extractArray[0].extractNonHdr.action =
            e_FM_PCD_ACTION_NONE;
    p_Scheme->keyExtractAndHashParams.extractArray[0].extractNonHdr.offset = 20;
    p_Scheme->keyExtractAndHashParams.extractArray[0].extractNonHdr.size = 4;
    p_Scheme->keyExtractAndHashParams.extractArray[1].type =
            e_FM_PCD_EXTRACT_NON_HDR;
    p_Scheme->keyExtractAndHashParams.extractArray[1].extractNonHdr.src =
            e_FM_PCD_EXTRACT_FROM_DFLT_VALUE;
    p_Scheme->keyExtractAndHashParams.extractArray[1].extractNonHdr.action =
            e_FM_PCD_ACTION_NONE;
    p_Scheme->keyExtractAndHashParams.extractArray[1].extractNonHdr.offset = 0;
    p_Scheme->keyExtractAndHashParams.extractArray[1].extractNonHdr.size = 1;

    p_Scheme->keyExtractAndHashParams.privateDflt0 = 0x0;
    p_Scheme->keyExtractAndHashParams.privateDflt1 = 0x0;
    p_Scheme->keyExtractAndHashParams.numOfUsedDflts = 1;
    p_Scheme->keyExtractAndHashParams.dflts[0].type = e_FM_PCD_KG_GENERIC_NOT_FROM_DATA;
    p_Scheme->keyExtractAndHashParams.dflts[0].dfltSelect = e_FM_PCD_KG_DFLT_PRIVATE_0;
}