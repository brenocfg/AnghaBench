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
typedef  scalar_t__ t_Handle ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  hardwarePortId; int /*<<< orphan*/  h_FmPcd; int /*<<< orphan*/  h_Spinlock; } ;
typedef  TYPE_1__ t_FmPort ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ERROR_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_BUSY ; 
 scalar_t__ E_OK ; 
 scalar_t__ FmPcdPlcrFreeProfiles (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  NO_MSG ; 
 int /*<<< orphan*/  RELEASE_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  TRY_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

t_Error FM_PORT_PcdPlcrFreeProfiles(t_Handle h_FmPort)
{
    t_FmPort *p_FmPort = (t_FmPort*)h_FmPort;
    t_Error err = E_OK;

    if (!TRY_LOCK(p_FmPort->h_Spinlock, &p_FmPort->lock))
    {
        DBG(TRACE, ("FM Port Try Lock - BUSY"));
        return ERROR_CODE(E_BUSY);
    }

    err = FmPcdPlcrFreeProfiles(p_FmPort->h_FmPcd, p_FmPort->hardwarePortId);

    RELEASE_LOCK(p_FmPort->lock);

    if (err)
        RETURN_ERROR(MAJOR, err, NO_MSG);

    return E_OK;
}