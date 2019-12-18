#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_12__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  TYPE_8__* t_Handle ;
struct TYPE_31__ {scalar_t__ nextEngine; int statisticsEn; } ;
struct TYPE_32__ {int maxNumOfKeys; scalar_t__ statisticsMode; int numOfKeys; int keySize; void* maskSupport; TYPE_12__* keyParams; TYPE_3__ ccNextEngineParamsForMiss; } ;
struct TYPE_29__ {int size; int icIndxMask; scalar_t__ offset; int /*<<< orphan*/  action; int /*<<< orphan*/  src; } ;
struct TYPE_30__ {TYPE_1__ extractNonHdr; void* type; } ;
struct TYPE_36__ {int maxNumOfKeys; int hashResMask; scalar_t__ statisticsMode; int matchKeySize; int statsEnForMiss; struct TYPE_36__* h_MissStatsCounters; int /*<<< orphan*/  kgHashShift; TYPE_4__ keysParams; TYPE_2__ extractCcParams; scalar_t__ hashShift; void* isHashBucket; TYPE_3__ ccNextEngineParamsForMiss; } ;
typedef  TYPE_8__ t_FmPcdHashTableParams ;
typedef  TYPE_8__ t_FmPcdCcNodeParams ;
typedef  TYPE_8__ t_FmPcdCcNode ;
struct TYPE_33__ {TYPE_8__* h_CcNode; } ;
struct TYPE_35__ {TYPE_5__ ccParams; } ;
struct TYPE_34__ {TYPE_7__ params; void* statisticsEn; int /*<<< orphan*/  nextEngine; } ;
struct TYPE_28__ {TYPE_6__ ccNextEngineParams; } ;
typedef  TYPE_12__ t_FmPcdCcKeyParams ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ DIV_CEIL (int,int) ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  E_NULL_POINTER ; 
 void* FALSE ; 
 scalar_t__ FM_MURAM_AllocMem (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_MURAM_FreeMem (int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  FM_PCD_CC_AD_TABLE_ALIGN ; 
 int FM_PCD_CC_STATS_COUNTER_SIZE ; 
 int /*<<< orphan*/  FM_PCD_MatchTableDelete (TYPE_8__*) ; 
 TYPE_8__* FM_PCD_MatchTableSet (TYPE_8__*,TYPE_8__*) ; 
 int /*<<< orphan*/  FmPcdGetMuramHandle (TYPE_8__*) ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MINOR ; 
 scalar_t__ MatchTableSet (TYPE_8__*,TYPE_8__*,TYPE_8__*) ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_VALUE (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* TRUE ; 
 int /*<<< orphan*/  XX_Free (TYPE_8__*) ; 
 scalar_t__ XX_Malloc (int) ; 
 int /*<<< orphan*/  e_FM_PCD_ACTION_EXACT_MATCH ; 
 int /*<<< orphan*/  e_FM_PCD_ACTION_INDEXED_LOOKUP ; 
 int /*<<< orphan*/  e_FM_PCD_CC ; 
 scalar_t__ e_FM_PCD_CC_STATS_MODE_BYTE_AND_FRAME ; 
 scalar_t__ e_FM_PCD_CC_STATS_MODE_FRAME ; 
 scalar_t__ e_FM_PCD_CC_STATS_MODE_NONE ; 
 scalar_t__ e_FM_PCD_CC_STATS_MODE_RMON ; 
 int /*<<< orphan*/  e_FM_PCD_EXTRACT_FROM_HASH ; 
 int /*<<< orphan*/  e_FM_PCD_EXTRACT_FROM_KEY ; 
 void* e_FM_PCD_EXTRACT_NON_HDR ; 
 scalar_t__ e_FM_PCD_INVALID ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 

t_Handle FM_PCD_HashTableSet(t_Handle h_FmPcd, t_FmPcdHashTableParams *p_Param)
{
    t_FmPcdCcNode *p_CcNodeHashTbl;
    t_FmPcdCcNodeParams *p_IndxHashCcNodeParam, *p_ExactMatchCcNodeParam;
    t_FmPcdCcNode *p_CcNode;
    t_Handle h_MissStatsCounters = NULL;
    t_FmPcdCcKeyParams *p_HashKeyParams;
    int i;
    uint16_t numOfSets, numOfWays, countMask, onesCount = 0;
    bool statsEnForMiss = FALSE;
    t_Error err;

    SANITY_CHECK_RETURN_VALUE(h_FmPcd, E_INVALID_HANDLE, NULL);
    SANITY_CHECK_RETURN_VALUE(p_Param, E_NULL_POINTER, NULL);

    if (p_Param->maxNumOfKeys == 0)
    {
        REPORT_ERROR(MINOR, E_INVALID_VALUE, ("Max number of keys must be higher then 0"));
        return NULL;
    }

    if (p_Param->hashResMask == 0)
    {
        REPORT_ERROR(MINOR, E_INVALID_VALUE, ("Hash result mask must differ from 0"));
        return NULL;
    }

    /*Fix: QorIQ SDK / QSDK-2131*/
    if (p_Param->ccNextEngineParamsForMiss.nextEngine == e_FM_PCD_INVALID)
    {
        REPORT_ERROR(MAJOR, E_INVALID_VALUE, ("Next PCD Engine for on-miss entry is invalid. On-miss entry is always required. You can use e_FM_PCD_DONE."));
        return NULL;
    }

#if (DPAA_VERSION >= 11)
    if (p_Param->statisticsMode == e_FM_PCD_CC_STATS_MODE_RMON)
    {
        REPORT_ERROR(MAJOR, E_INVALID_VALUE,
                ("RMON statistics mode is not supported for hash table"));
        return NULL;
    }
#endif /* (DPAA_VERSION >= 11) */

    p_ExactMatchCcNodeParam = (t_FmPcdCcNodeParams*)XX_Malloc(
            sizeof(t_FmPcdCcNodeParams));
    if (!p_ExactMatchCcNodeParam)
    {
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("p_ExactMatchCcNodeParam"));
        return NULL;
    }
    memset(p_ExactMatchCcNodeParam, 0, sizeof(t_FmPcdCcNodeParams));

    p_IndxHashCcNodeParam = (t_FmPcdCcNodeParams*)XX_Malloc(
            sizeof(t_FmPcdCcNodeParams));
    if (!p_IndxHashCcNodeParam)
    {
        XX_Free(p_ExactMatchCcNodeParam);
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("p_IndxHashCcNodeParam"));
        return NULL;
    }
    memset(p_IndxHashCcNodeParam, 0, sizeof(t_FmPcdCcNodeParams));

    /* Calculate number of sets and number of ways of the hash table */
    countMask = (uint16_t)(p_Param->hashResMask >> 4);
    while (countMask)
    {
        onesCount++;
        countMask = (uint16_t)(countMask >> 1);
    }

    numOfSets = (uint16_t)(1 << onesCount);
    numOfWays = (uint16_t)DIV_CEIL(p_Param->maxNumOfKeys, numOfSets);

    if (p_Param->maxNumOfKeys % numOfSets)
        DBG(INFO, ("'maxNumOfKeys' is not a multiple of hash number of ways, so number of ways will be rounded up"));

    if ((p_Param->statisticsMode == e_FM_PCD_CC_STATS_MODE_FRAME)
            || (p_Param->statisticsMode == e_FM_PCD_CC_STATS_MODE_BYTE_AND_FRAME))
    {
        /* Allocating a statistics counters table that will be used by all
         'miss' entries of the hash table */
        h_MissStatsCounters = (t_Handle)FM_MURAM_AllocMem(
                FmPcdGetMuramHandle(h_FmPcd), 2 * FM_PCD_CC_STATS_COUNTER_SIZE,
                FM_PCD_CC_AD_TABLE_ALIGN);
        if (!h_MissStatsCounters)
        {
            REPORT_ERROR(MAJOR, E_NO_MEMORY, ("MURAM allocation for statistics table for hash miss"));
            XX_Free(p_IndxHashCcNodeParam);
            XX_Free(p_ExactMatchCcNodeParam);
            return NULL;
        }
        memset(h_MissStatsCounters, 0, (2 * FM_PCD_CC_STATS_COUNTER_SIZE));

        /* Always enable statistics for 'miss', so that a statistics AD will be
         initialized from the start. We'll store the requested 'statistics enable'
         value and it will be used when statistics are read by the user. */
        statsEnForMiss = p_Param->ccNextEngineParamsForMiss.statisticsEn;
        p_Param->ccNextEngineParamsForMiss.statisticsEn = TRUE;
    }

    /* Building exact-match node params, will be used to create the hash buckets */
    p_ExactMatchCcNodeParam->extractCcParams.type = e_FM_PCD_EXTRACT_NON_HDR;

    p_ExactMatchCcNodeParam->extractCcParams.extractNonHdr.src =
            e_FM_PCD_EXTRACT_FROM_KEY;
    p_ExactMatchCcNodeParam->extractCcParams.extractNonHdr.action =
            e_FM_PCD_ACTION_EXACT_MATCH;
    p_ExactMatchCcNodeParam->extractCcParams.extractNonHdr.offset = 0;
    p_ExactMatchCcNodeParam->extractCcParams.extractNonHdr.size =
            p_Param->matchKeySize;

    p_ExactMatchCcNodeParam->keysParams.maxNumOfKeys = numOfWays;
    p_ExactMatchCcNodeParam->keysParams.maskSupport = FALSE;
    p_ExactMatchCcNodeParam->keysParams.statisticsMode =
            p_Param->statisticsMode;
    p_ExactMatchCcNodeParam->keysParams.numOfKeys = 0;
    p_ExactMatchCcNodeParam->keysParams.keySize = p_Param->matchKeySize;
    p_ExactMatchCcNodeParam->keysParams.ccNextEngineParamsForMiss =
            p_Param->ccNextEngineParamsForMiss;

    p_HashKeyParams = p_IndxHashCcNodeParam->keysParams.keyParams;

    for (i = 0; i < numOfSets; i++)
    {
        /* Each exact-match node will be marked as a 'bucket' and provided with
           a pointer to statistics counters, to be used for 'miss' entry
           statistics */
        p_CcNode = (t_FmPcdCcNode *)XX_Malloc(sizeof(t_FmPcdCcNode));
        if (!p_CcNode)
            break;
        memset(p_CcNode, 0, sizeof(t_FmPcdCcNode));

        p_CcNode->isHashBucket = TRUE;
        p_CcNode->h_MissStatsCounters = h_MissStatsCounters;

        err = MatchTableSet(h_FmPcd, p_CcNode, p_ExactMatchCcNodeParam);
        if (err)
            break;

        p_HashKeyParams[i].ccNextEngineParams.nextEngine = e_FM_PCD_CC;
        p_HashKeyParams[i].ccNextEngineParams.statisticsEn = FALSE;
        p_HashKeyParams[i].ccNextEngineParams.params.ccParams.h_CcNode =
                p_CcNode;
    }

    if (i < numOfSets)
    {
        for (i = i - 1; i >= 0; i--)
            FM_PCD_MatchTableDelete(
                    p_HashKeyParams[i].ccNextEngineParams.params.ccParams.h_CcNode);

        FM_MURAM_FreeMem(FmPcdGetMuramHandle(h_FmPcd), h_MissStatsCounters);

        REPORT_ERROR(MAJOR, E_NULL_POINTER, NO_MSG);
        XX_Free(p_IndxHashCcNodeParam);
        XX_Free(p_ExactMatchCcNodeParam);
        return NULL;
    }

    /* Creating indexed-hash CC node */
    p_IndxHashCcNodeParam->extractCcParams.type = e_FM_PCD_EXTRACT_NON_HDR;
    p_IndxHashCcNodeParam->extractCcParams.extractNonHdr.src =
            e_FM_PCD_EXTRACT_FROM_HASH;
    p_IndxHashCcNodeParam->extractCcParams.extractNonHdr.action =
            e_FM_PCD_ACTION_INDEXED_LOOKUP;
    p_IndxHashCcNodeParam->extractCcParams.extractNonHdr.icIndxMask =
            p_Param->hashResMask;
    p_IndxHashCcNodeParam->extractCcParams.extractNonHdr.offset =
            p_Param->hashShift;
    p_IndxHashCcNodeParam->extractCcParams.extractNonHdr.size = 2;

    p_IndxHashCcNodeParam->keysParams.maxNumOfKeys = numOfSets;
    p_IndxHashCcNodeParam->keysParams.maskSupport = FALSE;
    p_IndxHashCcNodeParam->keysParams.statisticsMode =
            e_FM_PCD_CC_STATS_MODE_NONE;
    /* Number of keys of this node is number of sets of the hash */
    p_IndxHashCcNodeParam->keysParams.numOfKeys = numOfSets;
    p_IndxHashCcNodeParam->keysParams.keySize = 2;

    p_CcNodeHashTbl = FM_PCD_MatchTableSet(h_FmPcd, p_IndxHashCcNodeParam);

    if (p_CcNodeHashTbl)
    {
        p_CcNodeHashTbl->kgHashShift = p_Param->kgHashShift;

        /* Storing the allocated counters for buckets 'miss' in the hash table
         and if statistics for miss were enabled. */
        p_CcNodeHashTbl->h_MissStatsCounters = h_MissStatsCounters;
        p_CcNodeHashTbl->statsEnForMiss = statsEnForMiss;
    }

    XX_Free(p_IndxHashCcNodeParam);
    XX_Free(p_ExactMatchCcNodeParam);

    return p_CcNodeHashTbl;
}