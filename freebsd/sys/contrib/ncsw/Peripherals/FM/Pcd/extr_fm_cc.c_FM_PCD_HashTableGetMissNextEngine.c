#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
struct TYPE_10__ {size_t numOfKeys; TYPE_3__* keyAndNextEngineParams; } ;
typedef  TYPE_4__ t_FmPcdCcNode ;
typedef  int /*<<< orphan*/  t_FmPcdCcNextEngineParams ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_7__ {TYPE_4__* h_CcNode; } ;
struct TYPE_8__ {TYPE_1__ ccParams; } ;
struct TYPE_11__ {TYPE_2__ params; } ;
struct TYPE_9__ {TYPE_5__ nextEngineParams; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_5__*,int) ; 

t_Error FM_PCD_HashTableGetMissNextEngine(
        t_Handle h_HashTbl,
        t_FmPcdCcNextEngineParams *p_FmPcdCcNextEngineParams)
{
    t_FmPcdCcNode *p_HashTbl = (t_FmPcdCcNode *)h_HashTbl;
    t_FmPcdCcNode *p_HashBucket;

    SANITY_CHECK_RETURN_ERROR(p_HashTbl, E_INVALID_HANDLE);

    /* Miss next engine of each bucket was initialized with the next engine of the hash table */
    p_HashBucket =
            p_HashTbl->keyAndNextEngineParams[0].nextEngineParams.params.ccParams.h_CcNode;

    memcpy(p_FmPcdCcNextEngineParams,
           &p_HashBucket->keyAndNextEngineParams[p_HashBucket->numOfKeys].nextEngineParams,
           sizeof(t_FmPcdCcNextEngineParams));

    return E_OK;
}