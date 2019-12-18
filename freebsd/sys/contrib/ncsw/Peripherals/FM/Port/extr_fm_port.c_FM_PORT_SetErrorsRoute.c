#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_9__ {int majorRev; } ;
struct TYPE_13__ {int portType; TYPE_4__* p_FmPortBmiRegs; TYPE_1__ fmRevInfo; int /*<<< orphan*/  port; } ;
typedef  TYPE_5__ t_FmPort ;
struct TYPE_14__ {int /*<<< orphan*/  errorsDiscardMask; } ;
typedef  TYPE_6__ t_FmPcdCtrlParamsPage ;
typedef  int /*<<< orphan*/  t_Error ;
typedef  int fmPortFrameErrSelect_t ;
struct TYPE_11__ {int /*<<< orphan*/  fmbm_ofsdm; } ;
struct TYPE_10__ {int /*<<< orphan*/  fmbm_rfsdm; } ;
struct TYPE_12__ {TYPE_3__ ohPortBmiRegs; TYPE_2__ rxPortBmiRegs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_6__*) ; 
 int /*<<< orphan*/  E_INVALID_OPERATION ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  FmPortSetGprFunc (TYPE_5__*,int /*<<< orphan*/ ,void**) ; 
 int GET_UINT32 (int /*<<< orphan*/  volatile) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/  volatile*) ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  e_FM_PORT_GPR_MURAM_PAGE ; 
 int e_FM_PORT_TYPE_OH_OFFLINE_PARSING ; 
 int e_FM_PORT_TYPE_RX ; 
 int e_FM_PORT_TYPE_RX_10G ; 
 int fman_port_set_err_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

t_Error FM_PORT_SetErrorsRoute(t_Handle h_FmPort, fmPortFrameErrSelect_t errs)
{
    t_FmPort *p_FmPort = (t_FmPort*)h_FmPort;
    volatile uint32_t *p_ErrDiscard = NULL;
    int err;

    UNUSED(p_ErrDiscard);
    err = fman_port_set_err_mask(&p_FmPort->port, (uint32_t)errs);
    if (err != 0)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("fman_port_set_err_mask"));

#ifdef FM_ERROR_VSP_NO_MATCH_SW006
    if (p_FmPort->fmRevInfo.majorRev >= 6)
    {
        t_FmPcdCtrlParamsPage *p_ParamsPage;

        FmPortSetGprFunc(p_FmPort, e_FM_PORT_GPR_MURAM_PAGE,
                         (void**)&p_ParamsPage);
        ASSERT_COND(p_ParamsPage);
        switch (p_FmPort->portType)
        {
            case (e_FM_PORT_TYPE_RX_10G):
            case (e_FM_PORT_TYPE_RX):
                p_ErrDiscard =
                        &p_FmPort->p_FmPortBmiRegs->rxPortBmiRegs.fmbm_rfsdm;
                break;
            case (e_FM_PORT_TYPE_OH_OFFLINE_PARSING):
                p_ErrDiscard =
                        &p_FmPort->p_FmPortBmiRegs->ohPortBmiRegs.fmbm_ofsdm;
                break;
            default:
                RETURN_ERROR(
                        MAJOR, E_INVALID_OPERATION,
                        ("available for Rx and offline parsing ports only"));
        }
        WRITE_UINT32(p_ParamsPage->errorsDiscardMask,
                     GET_UINT32(*p_ErrDiscard) | errs);
    }
#endif /* FM_ERROR_VSP_NO_MATCH_SW006 */

    return E_OK;
}