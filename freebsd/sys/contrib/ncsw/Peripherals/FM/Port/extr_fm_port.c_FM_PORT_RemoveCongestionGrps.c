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
typedef  int uint8_t ;
typedef  size_t uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_9__ {int majorRev; } ;
typedef  TYPE_2__ t_FmRevisionInfo ;
struct TYPE_10__ {size_t numOfCongestionGrpsToConsider; int* congestionGrpsToConsider; } ;
typedef  TYPE_3__ t_FmPortCongestionGrps ;
struct TYPE_8__ {int majorRev; } ;
struct TYPE_11__ {scalar_t__ portType; int /*<<< orphan*/  port; int /*<<< orphan*/  h_Fm; TYPE_1__ fmRevInfo; } ;
typedef  TYPE_4__ t_FmPort ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_NOT_SUPPORTED ; 
 scalar_t__ E_OK ; 
 int FMAN_PORT_CG_MAP_NUM ; 
 int /*<<< orphan*/  FM_GetRevision (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ FmSetCongestionGroupPFCpriority (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ e_FM_PORT_TYPE_OH_OFFLINE_PARSING ; 
 scalar_t__ e_FM_PORT_TYPE_RX ; 
 scalar_t__ e_FM_PORT_TYPE_RX_10G ; 
 int fman_port_remove_congestion_grps (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 

t_Error FM_PORT_RemoveCongestionGrps(t_Handle h_FmPort,
                                     t_FmPortCongestionGrps *p_CongestionGrps)
{
    t_FmPort *p_FmPort = (t_FmPort*)h_FmPort;
    uint8_t mod, index;
    uint32_t i, grpsMap[FMAN_PORT_CG_MAP_NUM];
    int err;

    SANITY_CHECK_RETURN_ERROR(p_FmPort, E_INVALID_HANDLE);

    {
#ifdef FM_NO_OP_OBSERVED_CGS
        t_FmRevisionInfo revInfo;

        FM_GetRevision(p_FmPort->h_Fm, &revInfo);
        if (revInfo.majorRev != 4)
        {
            if ((p_FmPort->portType != e_FM_PORT_TYPE_RX_10G) &&
                    (p_FmPort->portType != e_FM_PORT_TYPE_RX))
            RETURN_ERROR(MAJOR, E_NOT_SUPPORTED, ("Available for Rx ports only"));
        }
        else
#endif /* FM_NO_OP_OBSERVED_CGS */
        if ((p_FmPort->portType != e_FM_PORT_TYPE_RX_10G)
                && (p_FmPort->portType != e_FM_PORT_TYPE_RX)
                && (p_FmPort->portType != e_FM_PORT_TYPE_OH_OFFLINE_PARSING))
            RETURN_ERROR(MAJOR, E_NOT_SUPPORTED,
                         ("Available for Rx & OP ports only"));
    }

    /* Prepare groups map array */
    memset(grpsMap, 0, FMAN_PORT_CG_MAP_NUM * sizeof(uint32_t));
    for (i = 0; i < p_CongestionGrps->numOfCongestionGrpsToConsider; i++)
    {
        index = (uint8_t)(p_CongestionGrps->congestionGrpsToConsider[i] / 32);
        mod = (uint8_t)(p_CongestionGrps->congestionGrpsToConsider[i] % 32);
        if (p_FmPort->fmRevInfo.majorRev != 4)
            grpsMap[7 - index] |= (uint32_t)(1 << mod);
        else
            grpsMap[0] |= (uint32_t)(1 << mod);
    }

#if (DPAA_VERSION >= 11)
    for (i = 0; i < p_CongestionGrps->numOfCongestionGrpsToConsider; i++)
    {
        t_Error err = FmSetCongestionGroupPFCpriority(
                p_FmPort->h_Fm, p_CongestionGrps->congestionGrpsToConsider[i],
                0);
        if (err)
            return err;
    }
#endif /* (DPAA_VERSION >= 11) */

    err = fman_port_remove_congestion_grps(&p_FmPort->port, grpsMap);
    if (err != 0)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE,
                     ("fman_port_remove_congestion_grps"));
    return E_OK;
}