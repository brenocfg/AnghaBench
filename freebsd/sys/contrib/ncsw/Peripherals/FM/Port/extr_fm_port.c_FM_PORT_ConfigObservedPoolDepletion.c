#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
struct TYPE_5__ {int /*<<< orphan*/  poolsParams; int /*<<< orphan*/  poolDepletionParams; } ;
typedef  TYPE_1__ t_FmPortObservedBufPoolDepletion ;
struct TYPE_6__ {scalar_t__ portType; int /*<<< orphan*/  extBufPools; struct TYPE_6__* p_FmPortDriverParam; int /*<<< orphan*/  bufPoolDepletion; int /*<<< orphan*/  enBufPoolDepletion; } ;
typedef  TYPE_2__ t_FmPort ;
typedef  int /*<<< orphan*/  t_FmExtPools ;
typedef  int /*<<< orphan*/  t_FmBufPoolDepletion ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_OPERATION ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ e_FM_PORT_TYPE_OH_OFFLINE_PARSING ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

t_Error FM_PORT_ConfigObservedPoolDepletion(
        t_Handle h_FmPort,
        t_FmPortObservedBufPoolDepletion *p_FmPortObservedBufPoolDepletion)
{
    t_FmPort *p_FmPort = (t_FmPort*)h_FmPort;

    SANITY_CHECK_RETURN_ERROR(p_FmPort, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_FmPort->p_FmPortDriverParam, E_INVALID_HANDLE);
    if (p_FmPort->portType != e_FM_PORT_TYPE_OH_OFFLINE_PARSING)
        RETURN_ERROR(MAJOR, E_INVALID_OPERATION,
                     ("available for OP ports only"));

    p_FmPort->p_FmPortDriverParam->enBufPoolDepletion = TRUE;
    memcpy(&p_FmPort->p_FmPortDriverParam->bufPoolDepletion,
           &p_FmPortObservedBufPoolDepletion->poolDepletionParams,
           sizeof(t_FmBufPoolDepletion));
    memcpy(&p_FmPort->p_FmPortDriverParam->extBufPools,
           &p_FmPortObservedBufPoolDepletion->poolsParams,
           sizeof(t_FmExtPools));

    return E_OK;
}