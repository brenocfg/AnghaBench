#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t_Handle ;
struct TYPE_4__ {scalar_t__ nextEngine; } ;
typedef  TYPE_1__ t_FmPcdCcNextEngineParams ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 scalar_t__ E_NOT_SUPPORTED ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 scalar_t__ ValidateNextEngineParams (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_FM_PCD_CC_STATS_MODE_NONE ; 
 scalar_t__ e_FM_PCD_DONE ; 
 scalar_t__ e_FM_PCD_KG ; 
 scalar_t__ e_FM_PCD_PLCR ; 

__attribute__((used)) static t_Error MemberCheckParams(t_Handle                  h_FmPcd,
                                 t_FmPcdCcNextEngineParams *p_MemberParams)
{
    t_Error         err;


    if ((p_MemberParams->nextEngine != e_FM_PCD_DONE) &&
        (p_MemberParams->nextEngine != e_FM_PCD_KG)   &&
        (p_MemberParams->nextEngine != e_FM_PCD_PLCR))
        RETURN_ERROR(MAJOR, E_NOT_SUPPORTED, ("Next engine of a member should be MatchTable(cc) or Done or Policer"));

    /* check the regular parameters of the next engine */
    err = ValidateNextEngineParams(h_FmPcd, p_MemberParams, e_FM_PCD_CC_STATS_MODE_NONE);
    if (err)
        RETURN_ERROR(MAJOR, err, ("member next engine parameters"));

    return E_OK;
}