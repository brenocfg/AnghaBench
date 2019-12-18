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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_3__ {int /*<<< orphan*/  (* f_FM_MACSEC_ConfigPnExhaustionThreshold ) (scalar_t__,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ t_FmMacsecControllerDriver ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_NOT_SUPPORTED ; 
 int /*<<< orphan*/  MINOR ; 
 int /*<<< orphan*/  NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ) ; 

t_Error FM_MACSEC_ConfigPnExhaustionThreshold(t_Handle h_FmMacsec, uint32_t pnExhThr)
{
    t_FmMacsecControllerDriver *p_FmMacsecControllerDriver = (t_FmMacsecControllerDriver *)h_FmMacsec;

    SANITY_CHECK_RETURN_ERROR(p_FmMacsecControllerDriver, E_INVALID_HANDLE);

    if (p_FmMacsecControllerDriver->f_FM_MACSEC_ConfigPnExhaustionThreshold)
        return p_FmMacsecControllerDriver->f_FM_MACSEC_ConfigPnExhaustionThreshold(h_FmMacsec, pnExhThr);

    RETURN_ERROR(MINOR, E_NOT_SUPPORTED, NO_MSG);
}