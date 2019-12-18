#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int t_Handle ;
struct TYPE_2__ {scalar_t__ portType; int pcdEngines; int /*<<< orphan*/  lock; int /*<<< orphan*/ * h_ReassemblyTree; int /*<<< orphan*/  h_FmPcd; scalar_t__ includeInPrsStatistics; int /*<<< orphan*/  hardwarePortId; int /*<<< orphan*/  netEnvId; int /*<<< orphan*/  h_Spinlock; scalar_t__ imEn; int /*<<< orphan*/  p_FmPortDriverParam; } ;
typedef  TYPE_1__ t_FmPort ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ DeletePcd (int) ; 
 scalar_t__ DetachPCD (int) ; 
 scalar_t__ ERROR_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_BUSY ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 scalar_t__ E_INVALID_OPERATION ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 scalar_t__ E_OK ; 
 scalar_t__ FALSE ; 
 scalar_t__ FM_PCD_CcRootDelete (int /*<<< orphan*/ *) ; 
 int FM_PCD_PRS ; 
 int /*<<< orphan*/  FmPcdDecNetEnvOwners (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdLockTryLockAll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdLockUnlockAll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdPrsIncludePortInStatistics (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  MAJOR ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  RELEASE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  TRY_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ e_FM_PORT_TYPE_OH_OFFLINE_PARSING ; 
 scalar_t__ e_FM_PORT_TYPE_RX ; 
 scalar_t__ e_FM_PORT_TYPE_RX_10G ; 

t_Error FM_PORT_DeletePCD(t_Handle h_FmPort)
{
    t_FmPort *p_FmPort = (t_FmPort*)h_FmPort;
    t_Error err = E_OK;

    SANITY_CHECK_RETURN_ERROR(h_FmPort, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(!p_FmPort->p_FmPortDriverParam, E_INVALID_STATE);

    if (p_FmPort->imEn)
        RETURN_ERROR(MAJOR, E_INVALID_OPERATION,
                     ("available for non-independant mode ports only"));

    if ((p_FmPort->portType != e_FM_PORT_TYPE_RX_10G)
            && (p_FmPort->portType != e_FM_PORT_TYPE_RX)
            && (p_FmPort->portType != e_FM_PORT_TYPE_OH_OFFLINE_PARSING))
        RETURN_ERROR( MAJOR, E_INVALID_OPERATION,
                     ("available for Rx and offline parsing ports only"));

    if (!TRY_LOCK(p_FmPort->h_Spinlock, &p_FmPort->lock))
    {
        DBG(TRACE, ("FM Port Try Lock - BUSY"));
        return ERROR_CODE(E_BUSY);
    }

    err = DetachPCD(h_FmPort);
    if (err)
    {
        RELEASE_LOCK(p_FmPort->lock);
        RETURN_ERROR(MAJOR, err, NO_MSG);
    }

    FmPcdDecNetEnvOwners(p_FmPort->h_FmPcd, p_FmPort->netEnvId);

    /* we do it anyway, instead of checking if included */
    if ((p_FmPort->pcdEngines & FM_PCD_PRS) && p_FmPort->includeInPrsStatistics)
    {
        FmPcdPrsIncludePortInStatistics(p_FmPort->h_FmPcd,
                                        p_FmPort->hardwarePortId, FALSE);
        p_FmPort->includeInPrsStatistics = FALSE;
    }

    if (!FmPcdLockTryLockAll(p_FmPort->h_FmPcd))
    {
        RELEASE_LOCK(p_FmPort->lock);
        DBG(TRACE, ("Try LockAll - BUSY"));
        return ERROR_CODE(E_BUSY);
    }

    err = DeletePcd(h_FmPort);
    FmPcdLockUnlockAll(p_FmPort->h_FmPcd);
    if (err)
    {
        RELEASE_LOCK(p_FmPort->lock);
        RETURN_ERROR(MAJOR, err, NO_MSG);
    }

    if (p_FmPort->h_ReassemblyTree)
    {
        err = FM_PCD_CcRootDelete(p_FmPort->h_ReassemblyTree);
        if (err)
        {
            RELEASE_LOCK(p_FmPort->lock);
            RETURN_ERROR(MAJOR, err, NO_MSG);
        }
        p_FmPort->h_ReassemblyTree = NULL;
    }RELEASE_LOCK(p_FmPort->lock);

    return err;
}