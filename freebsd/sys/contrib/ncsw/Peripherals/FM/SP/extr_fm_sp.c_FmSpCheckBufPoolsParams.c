#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_9__ {int numOfPoolsUsed; TYPE_1__* extBufPool; } ;
typedef  TYPE_2__ t_FmExtPools ;
struct TYPE_10__ {scalar_t__ numOfPools; scalar_t__* poolsToConsiderForSingleMode; scalar_t__ singlePoolModeEnable; scalar_t__* poolsToConsider; scalar_t__ poolsGrpModeEnable; } ;
typedef  TYPE_3__ t_FmBufPoolDepletion ;
struct TYPE_11__ {int numOfBackupPools; int* poolIds; } ;
typedef  TYPE_4__ t_FmBackupBmPools ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_8__ {int id; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int BM_MAX_NUM_OF_POOLS ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_OK ; 
 int FALSE ; 
 int FM_PORT_MAX_NUM_OF_EXT_POOLS ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int TRUE ; 

t_Error FmSpCheckBufPoolsParams(t_FmExtPools            *p_FmExtPools,
                                t_FmBackupBmPools       *p_FmBackupBmPools,
                                t_FmBufPoolDepletion    *p_FmBufPoolDepletion)
{

    int         i = 0, j = 0;
    bool        found;
    uint8_t     count = 0;

    if (p_FmExtPools)
    {
        if (p_FmExtPools->numOfPoolsUsed > FM_PORT_MAX_NUM_OF_EXT_POOLS)
                RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("numOfPoolsUsed can't be larger than %d", FM_PORT_MAX_NUM_OF_EXT_POOLS));

        for (i=0;i<p_FmExtPools->numOfPoolsUsed;i++)
        {
            if (p_FmExtPools->extBufPool[i].id >= BM_MAX_NUM_OF_POOLS)
                RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("extBufPools.extBufPool[%d].id can't be larger than %d", i, BM_MAX_NUM_OF_POOLS));
            if (!p_FmExtPools->extBufPool[i].size)
                RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("extBufPools.extBufPool[%d].size is 0", i));
        }
    }
    if (!p_FmExtPools && (p_FmBackupBmPools || p_FmBufPoolDepletion))
          RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("backupBmPools ot bufPoolDepletion can not be defined without external pools"));

    /* backup BM pools indication is valid only for some chip derivatives
       (limited by the config routine) */
    if (p_FmBackupBmPools)
    {
        if (p_FmBackupBmPools->numOfBackupPools >= p_FmExtPools->numOfPoolsUsed)
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("p_BackupBmPools must be smaller than extBufPools.numOfPoolsUsed"));
        found = FALSE;
        for (i = 0;i<p_FmBackupBmPools->numOfBackupPools;i++)
        {

            for (j=0;j<p_FmExtPools->numOfPoolsUsed;j++)
            {
                if (p_FmBackupBmPools->poolIds[i] == p_FmExtPools->extBufPool[j].id)
                {
                    found = TRUE;
                    break;
                }
            }
            if (!found)
                RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("All p_BackupBmPools.poolIds must be included in extBufPools.extBufPool[n].id"));
            else
                found = FALSE;
        }
    }

    /* up to extBufPools.numOfPoolsUsed pools may be defined */
    if (p_FmBufPoolDepletion && p_FmBufPoolDepletion->poolsGrpModeEnable)
    {
        if ((p_FmBufPoolDepletion->numOfPools > p_FmExtPools->numOfPoolsUsed))
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("bufPoolDepletion.numOfPools can't be larger than %d and can't be larger than numOfPoolsUsed", FM_PORT_MAX_NUM_OF_EXT_POOLS));

        if (!p_FmBufPoolDepletion->numOfPools)
          RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("bufPoolDepletion.numOfPoolsToConsider can not be 0 when poolsGrpModeEnable=TRUE"));

        found = FALSE;
        count = 0;
        /* for each pool that is in poolsToConsider, check if it is defined
           in extBufPool */
        for (i=0;i<BM_MAX_NUM_OF_POOLS;i++)
        {
            if (p_FmBufPoolDepletion->poolsToConsider[i])
            {
                for (j=0;j<p_FmExtPools->numOfPoolsUsed;j++)
                 {
                    if (i == p_FmExtPools->extBufPool[j].id)
                    {
                        found = TRUE;
                        count++;
                        break;
                    }
                 }
                if (!found)
                    RETURN_ERROR(MAJOR, E_INVALID_STATE, ("Pools selected for depletion are not used."));
                else
                    found = FALSE;
            }
        }
        /* check that the number of pools that we have checked is equal to the number announced by the user */
        if (count != p_FmBufPoolDepletion->numOfPools)
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("bufPoolDepletion.numOfPools is larger than the number of pools defined."));
    }

    if (p_FmBufPoolDepletion && p_FmBufPoolDepletion->singlePoolModeEnable)
    {
        /* calculate vector for number of pools depletion */
        found = FALSE;
        count = 0;
        for (i=0;i<BM_MAX_NUM_OF_POOLS;i++)
        {
            if (p_FmBufPoolDepletion->poolsToConsiderForSingleMode[i])
            {
                for (j=0;j<p_FmExtPools->numOfPoolsUsed;j++)
                {
                    if (i == p_FmExtPools->extBufPool[j].id)
                    {
                        found = TRUE;
                        count++;
                        break;
                    }
                }
                if (!found)
                    RETURN_ERROR(MAJOR, E_INVALID_STATE, ("Pools selected for depletion are not used."));
                else
                    found = FALSE;
            }
        }
        if (!count)
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("No pools defined for single buffer mode pool depletion."));
    }

    return E_OK;
}