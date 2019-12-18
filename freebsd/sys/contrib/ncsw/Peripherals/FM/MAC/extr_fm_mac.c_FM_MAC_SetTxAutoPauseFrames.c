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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_3__ {int /*<<< orphan*/  (* f_FM_MAC_SetTxAutoPauseFrames ) (scalar_t__,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ t_FmMacControllerDriver ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_NOT_SUPPORTED ; 
 int /*<<< orphan*/  MINOR ; 
 int /*<<< orphan*/  NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ) ; 

t_Error FM_MAC_SetTxAutoPauseFrames(t_Handle h_FmMac,
                                    uint16_t pauseTime)
{
    t_FmMacControllerDriver *p_FmMacControllerDriver = (t_FmMacControllerDriver *)h_FmMac;

    SANITY_CHECK_RETURN_ERROR(p_FmMacControllerDriver, E_INVALID_HANDLE);

    if (p_FmMacControllerDriver->f_FM_MAC_SetTxAutoPauseFrames)
        return p_FmMacControllerDriver->f_FM_MAC_SetTxAutoPauseFrames(h_FmMac,
                                                                      pauseTime);

    RETURN_ERROR(MINOR, E_NOT_SUPPORTED, NO_MSG);
}