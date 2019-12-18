#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_5__ {scalar_t__ guestId; int /*<<< orphan*/  f_Exception; TYPE_1__* p_BmDriverParams; } ;
typedef  TYPE_2__ t_Bm ;
struct TYPE_4__ {scalar_t__ partBpidBase; scalar_t__ partNumOfPools; int totalNumOfBuffers; } ;

/* Variables and functions */
 scalar_t__ BM_MAX_NUM_OF_POOLS ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  MAJOR ; 
 int MEGABYTE ; 
 scalar_t__ NCSW_MASTER_ID ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static t_Error CheckBmParameters(t_Bm *p_Bm)
{
    if ((p_Bm->p_BmDriverParams->partBpidBase + p_Bm->p_BmDriverParams->partNumOfPools) > BM_MAX_NUM_OF_POOLS)
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("partBpidBase+partNumOfPools out of range!!!"));

    if (p_Bm->guestId == NCSW_MASTER_ID)
    {
        if (!p_Bm->p_BmDriverParams->totalNumOfBuffers)
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("totalNumOfBuffers must be larger than '0'!!!"));
        if (p_Bm->p_BmDriverParams->totalNumOfBuffers > (128*MEGABYTE))
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("totalNumOfBuffers must be equal or smaller than 128M!!!"));
        if(!p_Bm->f_Exception)
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("Exceptions callback not provided"));
    }

    return E_OK;
}