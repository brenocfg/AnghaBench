#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
struct TYPE_5__ {scalar_t__ dataAlign; } ;
struct TYPE_4__ {TYPE_2__ bufferPrefixContent; struct TYPE_4__* p_FmPortDriverParam; } ;
typedef  TYPE_1__ t_FmPort ;
typedef  int /*<<< orphan*/  t_FmBufferPrefixContent ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 scalar_t__ DEFAULT_PORT_bufferPrefixContent_dataAlign ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

t_Error FM_PORT_ConfigBufferPrefixContent(
        t_Handle h_FmPort, t_FmBufferPrefixContent *p_FmBufferPrefixContent)
{
    t_FmPort *p_FmPort = (t_FmPort*)h_FmPort;

    SANITY_CHECK_RETURN_ERROR(p_FmPort, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_FmPort->p_FmPortDriverParam, E_INVALID_HANDLE);

    memcpy(&p_FmPort->p_FmPortDriverParam->bufferPrefixContent,
           p_FmBufferPrefixContent, sizeof(t_FmBufferPrefixContent));
    /* if dataAlign was not initialized by user, we return to driver's default */
    if (!p_FmPort->p_FmPortDriverParam->bufferPrefixContent.dataAlign)
        p_FmPort->p_FmPortDriverParam->bufferPrefixContent.dataAlign =
                DEFAULT_PORT_bufferPrefixContent_dataAlign;

    return E_OK;
}