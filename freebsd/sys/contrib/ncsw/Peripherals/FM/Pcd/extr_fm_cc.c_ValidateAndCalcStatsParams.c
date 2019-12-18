#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int uint16_t ;
struct TYPE_11__ {int* frameLengthRanges; TYPE_2__* keyParams; } ;
struct TYPE_12__ {TYPE_3__ keysParams; } ;
typedef  TYPE_4__ t_FmPcdCcNodeParams ;
struct TYPE_13__ {int statisticsMode; size_t numOfKeys; } ;
typedef  TYPE_5__ t_FmPcdCcNode ;
typedef  int /*<<< orphan*/  t_Error ;
typedef  int e_FmPcdCcStatsMode ;
struct TYPE_9__ {int /*<<< orphan*/  statisticsEn; } ;
struct TYPE_10__ {TYPE_1__ ccNextEngineParams; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_OK ; 
 int FM_PCD_CC_STATS_COUNTER_SIZE ; 
 size_t FM_PCD_CC_STATS_MAX_NUM_OF_FLR ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UNUSED (TYPE_4__*) ; 
#define  e_FM_PCD_CC_STATS_MODE_BYTE_AND_FRAME 131 
#define  e_FM_PCD_CC_STATS_MODE_FRAME 130 
#define  e_FM_PCD_CC_STATS_MODE_NONE 129 
#define  e_FM_PCD_CC_STATS_MODE_RMON 128 

__attribute__((used)) static t_Error ValidateAndCalcStatsParams(t_FmPcdCcNode *p_CcNode,
                                          t_FmPcdCcNodeParams *p_CcNodeParam,
                                          uint32_t *p_NumOfRanges,
                                          uint32_t *p_CountersArraySize)
{
    e_FmPcdCcStatsMode statisticsMode = p_CcNode->statisticsMode;
    uint32_t i;

    UNUSED(p_CcNodeParam);

    switch (statisticsMode)
    {
        case e_FM_PCD_CC_STATS_MODE_NONE:
            for (i = 0; i < p_CcNode->numOfKeys; i++)
                if (p_CcNodeParam->keysParams.keyParams[i].ccNextEngineParams.statisticsEn)
                    RETURN_ERROR(
                            MAJOR,
                            E_INVALID_VALUE,
                            ("Statistics cannot be enabled for key %d when statistics mode was set to 'NONE'", i));
            return E_OK;

        case e_FM_PCD_CC_STATS_MODE_FRAME:
        case e_FM_PCD_CC_STATS_MODE_BYTE_AND_FRAME:
            *p_NumOfRanges = 1;
            *p_CountersArraySize = 2 * FM_PCD_CC_STATS_COUNTER_SIZE;
            return E_OK;

#if (DPAA_VERSION >= 11)
        case e_FM_PCD_CC_STATS_MODE_RMON:
        {
            uint16_t *p_FrameLengthRanges =
                    p_CcNodeParam->keysParams.frameLengthRanges;
            uint32_t i;

            if (p_FrameLengthRanges[0] <= 0)
                RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("Statistics mode"));

            if (p_FrameLengthRanges[0] == 0xFFFF)
            {
                *p_NumOfRanges = 1;
                *p_CountersArraySize = 2 * FM_PCD_CC_STATS_COUNTER_SIZE;
                return E_OK;
            }

            for (i = 1; i < FM_PCD_CC_STATS_MAX_NUM_OF_FLR; i++)
            {
                if (p_FrameLengthRanges[i - 1] >= p_FrameLengthRanges[i])
                    RETURN_ERROR(
                            MAJOR,
                            E_INVALID_VALUE,
                            ("Frame length range must be larger at least by 1 from preceding range"));

                /* Stop when last range is reached */
                if (p_FrameLengthRanges[i] == 0xFFFF)
                    break;
            }

            if ((i >= FM_PCD_CC_STATS_MAX_NUM_OF_FLR)
                    || (p_FrameLengthRanges[i] != 0xFFFF))
                RETURN_ERROR(MAJOR, E_INVALID_VALUE,
                             ("Last Frame length range must be 0xFFFF"));

            *p_NumOfRanges = i + 1;

            /* Allocate an extra counter for byte count, as counters
             array always begins with byte count */
            *p_CountersArraySize = (*p_NumOfRanges + 1)
                    * FM_PCD_CC_STATS_COUNTER_SIZE;

        }
            return E_OK;
#endif /* (DPAA_VERSION >= 11) */

        default:
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("Statistics mode"));
    }
}