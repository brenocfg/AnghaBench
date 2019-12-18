#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int mrblr; } ;
struct TYPE_7__ {scalar_t__ portType; TYPE_2__* p_FmPortDriverParam; TYPE_1__ im; } ;
typedef  TYPE_3__ t_FmPort ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_6__ {int liodnOffset; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_OK ; 
 int FM_LIODN_OFFSET_MASK ; 
 int /*<<< orphan*/  MAJOR ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  POWER_OF_2 (int) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ e_FM_PORT_TYPE_RX ; 
 scalar_t__ e_FM_PORT_TYPE_RX_10G ; 
 scalar_t__ e_FM_PORT_TYPE_TX ; 
 scalar_t__ e_FM_PORT_TYPE_TX_10G ; 

t_Error FmPortImCheckInitParameters(t_FmPort *p_FmPort)
{
    if ((p_FmPort->portType != e_FM_PORT_TYPE_RX) &&
        (p_FmPort->portType != e_FM_PORT_TYPE_RX_10G) &&
        (p_FmPort->portType != e_FM_PORT_TYPE_TX) &&
        (p_FmPort->portType != e_FM_PORT_TYPE_TX_10G))
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, NO_MSG);

    if ((p_FmPort->portType == e_FM_PORT_TYPE_RX) ||
        (p_FmPort->portType == e_FM_PORT_TYPE_RX_10G))
    {
        if (!POWER_OF_2(p_FmPort->im.mrblr))
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("max Rx buffer length must be power of 2!!!"));
        if (p_FmPort->im.mrblr < 256)
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("max Rx buffer length must at least 256!!!"));
        if (p_FmPort->p_FmPortDriverParam->liodnOffset & ~FM_LIODN_OFFSET_MASK)
            RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("liodnOffset is larger than %d", FM_LIODN_OFFSET_MASK+1));
    }

    return E_OK;
}