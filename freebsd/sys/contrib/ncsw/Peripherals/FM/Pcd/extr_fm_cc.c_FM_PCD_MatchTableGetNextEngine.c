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
typedef  int uint16_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_8__ {int numOfKeys; TYPE_1__* keyAndNextEngineParams; } ;
typedef  TYPE_2__ t_FmPcdCcNode ;
typedef  TYPE_2__ t_FmPcdCcNextEngineParams ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_7__ {int /*<<< orphan*/  nextEngineParams; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_NULL_POINTER ; 
 int /*<<< orphan*/  E_OK ; 
 int FM_PCD_MAX_NUM_OF_KEYS ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

t_Error FM_PCD_MatchTableGetNextEngine(
        t_Handle h_CcNode, uint16_t keyIndex,
        t_FmPcdCcNextEngineParams *p_FmPcdCcNextEngineParams)
{
    t_FmPcdCcNode *p_CcNode = (t_FmPcdCcNode *)h_CcNode;

    SANITY_CHECK_RETURN_ERROR(p_CcNode, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_FmPcdCcNextEngineParams, E_NULL_POINTER);

    if (keyIndex >= p_CcNode->numOfKeys)
        RETURN_ERROR(MAJOR, E_INVALID_STATE,
                     ("keyIndex exceeds current number of keys"));

    if (keyIndex > (FM_PCD_MAX_NUM_OF_KEYS - 1))
        RETURN_ERROR(
                MAJOR,
                E_INVALID_VALUE,
                ("keyIndex can not be larger than %d", (FM_PCD_MAX_NUM_OF_KEYS - 1)));

    memcpy(p_FmPcdCcNextEngineParams,
           &p_CcNode->keyAndNextEngineParams[keyIndex].nextEngineParams,
           sizeof(t_FmPcdCcNextEngineParams));

    return E_OK;
}