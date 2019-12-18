#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * t_Handle ;
struct TYPE_6__ {scalar_t__ guestMode; } ;
typedef  TYPE_1__ t_FmMacsecParams ;
typedef  int /*<<< orphan*/  t_FmMacsecControllerDriver ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 scalar_t__ FM_MACSEC_GUEST_Config (TYPE_1__*) ; 
 scalar_t__ FM_MACSEC_MASTER_Config (TYPE_1__*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_VALUE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

t_Handle FM_MACSEC_Config(t_FmMacsecParams *p_FmMacsecParam)
{
    t_FmMacsecControllerDriver *p_FmMacsecControllerDriver;

    SANITY_CHECK_RETURN_VALUE(p_FmMacsecParam, E_INVALID_HANDLE, NULL);

    if (p_FmMacsecParam->guestMode)
        p_FmMacsecControllerDriver = (t_FmMacsecControllerDriver *)FM_MACSEC_GUEST_Config(p_FmMacsecParam);
    else
        p_FmMacsecControllerDriver = (t_FmMacsecControllerDriver *)FM_MACSEC_MASTER_Config(p_FmMacsecParam);

    if (!p_FmMacsecControllerDriver)
        return NULL;

    return (t_Handle)p_FmMacsecControllerDriver;
}