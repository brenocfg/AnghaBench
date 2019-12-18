#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t_Handle ;
struct TYPE_3__ {int maxNumOfEntries; int numOfEntries; int /*<<< orphan*/ * nextEngineParams; } ;
typedef  TYPE_1__ t_FmPcdFrmReplicGroupParams ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 scalar_t__ E_INVALID_VALUE ; 
 scalar_t__ E_NOT_IN_RANGE ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  FM_PCD_FRM_REPLIC_MAX_NUM_OF_ENTRIES ; 
 int /*<<< orphan*/  IN_RANGE (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 scalar_t__ MemberCheckParams (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 

__attribute__((used)) static t_Error CheckParams(t_Handle                     h_FmPcd,
                           t_FmPcdFrmReplicGroupParams *p_ReplicGroupParam)
{
    int             i;
    t_Error         err;

    /* check that max num of entries is at least 2 */
    if (!IN_RANGE(2, p_ReplicGroupParam->maxNumOfEntries, FM_PCD_FRM_REPLIC_MAX_NUM_OF_ENTRIES))
        RETURN_ERROR(MAJOR, E_NOT_IN_RANGE, ("maxNumOfEntries in the frame replicator parameters should be 2-%d",FM_PCD_FRM_REPLIC_MAX_NUM_OF_ENTRIES));

    /* check that number of entries is greater than zero */
    if (!p_ReplicGroupParam->numOfEntries)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("numOFEntries in the frame replicator group should be greater than zero"));

    /* check that max num of entries is equal or greater than number of entries */
    if (p_ReplicGroupParam->maxNumOfEntries < p_ReplicGroupParam->numOfEntries)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("maxNumOfEntries should be equal or greater than numOfEntries"));

    for (i=0; i<p_ReplicGroupParam->numOfEntries; i++)
    {
        err = MemberCheckParams(h_FmPcd, &p_ReplicGroupParam->nextEngineParams[i]);
        if (err)
            RETURN_ERROR(MAJOR, err, ("member check parameters"));
    }
    return E_OK;
}