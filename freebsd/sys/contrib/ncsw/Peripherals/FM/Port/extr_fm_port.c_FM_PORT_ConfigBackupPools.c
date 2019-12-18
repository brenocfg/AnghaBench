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
typedef  scalar_t__ t_Handle ;
struct TYPE_3__ {scalar_t__ portType; int /*<<< orphan*/ * p_BackupBmPools; struct TYPE_3__* p_FmPortDriverParam; } ;
typedef  TYPE_1__ t_FmPort ;
typedef  int /*<<< orphan*/  t_FmBackupBmPools ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_OPERATION ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ XX_Malloc (int) ; 
 scalar_t__ e_FM_PORT_TYPE_RX ; 
 scalar_t__ e_FM_PORT_TYPE_RX_10G ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

t_Error FM_PORT_ConfigBackupPools(t_Handle h_FmPort,
                                  t_FmBackupBmPools *p_BackupBmPools)
{
    t_FmPort *p_FmPort = (t_FmPort*)h_FmPort;

    SANITY_CHECK_RETURN_ERROR(p_FmPort, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_FmPort->p_FmPortDriverParam, E_INVALID_HANDLE);
    if ((p_FmPort->portType != e_FM_PORT_TYPE_RX_10G)
            && (p_FmPort->portType != e_FM_PORT_TYPE_RX))
        RETURN_ERROR(MAJOR, E_INVALID_OPERATION,
                     ("available for Rx ports only"));

    p_FmPort->p_FmPortDriverParam->p_BackupBmPools =
            (t_FmBackupBmPools *)XX_Malloc(sizeof(t_FmBackupBmPools));
    if (!p_FmPort->p_FmPortDriverParam->p_BackupBmPools)
        RETURN_ERROR(MAJOR, E_NO_MEMORY, ("p_BackupBmPools allocation failed"));
    memcpy(p_FmPort->p_FmPortDriverParam->p_BackupBmPools, p_BackupBmPools,
           sizeof(t_FmBackupBmPools));

    return E_OK;
}