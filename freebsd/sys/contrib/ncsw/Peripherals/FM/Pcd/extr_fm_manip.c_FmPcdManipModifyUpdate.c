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
struct TYPE_3__ {int opcode; int shadowUpdateParams; int /*<<< orphan*/  h_Frag; } ;
typedef  TYPE_1__ t_FmPcdManip ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_OK ; 
 int HMAN_OC_CAPWAP_RMV_DTLS_IF_EXIST ; 
 int HMAN_OC_INSRT_HDR_BY_TEMPL_N_OR_FRAG_AFTER ; 
 int HMAN_OC_MV_INT_FRAME_HDR_FROM_FRM_TO_BUFFER_PREFFIX ; 
 int /*<<< orphan*/  MAJOR ; 
 int NUM_OF_TASKS ; 
 int OFFSET_OF_DATA ; 
 int OFFSET_OF_PR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UNUSED (int) ; 
 int /*<<< orphan*/  UpdateModifyCapwapFragmenation (TYPE_1__*,scalar_t__,int,scalar_t__) ; 

__attribute__((used)) static t_Error FmPcdManipModifyUpdate(t_Handle h_Manip, t_Handle h_Ad,
                                      bool validate, int level,
                                      t_Handle h_FmTree)
{

    t_FmPcdManip *p_Manip = (t_FmPcdManip *)h_Manip;
    t_Error err = E_OK;

    UNUSED(level);

    switch (p_Manip->opcode)
    {
#if (defined(FM_CAPWAP_SUPPORT) && (DPAA_VERSION == 10))
        case (HMAN_OC_MV_INT_FRAME_HDR_FROM_FRM_TO_BUFFER_PREFFIX):
        RETURN_ERROR(
                MAJOR,
                E_INVALID_STATE,
                ("modify node with this type of manipulation  is not suppported"));
        case (HMAN_OC_CAPWAP_RMV_DTLS_IF_EXIST):

        if (p_Manip->h_Frag)
        {
            if (!(p_Manip->shadowUpdateParams & NUM_OF_TASKS)
                    && !(p_Manip->shadowUpdateParams & OFFSET_OF_DATA)
                    && !(p_Manip->shadowUpdateParams & OFFSET_OF_PR))
            RETURN_ERROR(
                    MAJOR,
                    E_INVALID_STATE,
                    ("modify node with this type of manipulation requires manipulation be updated previously in SetPcd function"));
        }
        break;
        case (HMAN_OC_INSRT_HDR_BY_TEMPL_N_OR_FRAG_AFTER):
        if (p_Manip->h_Frag)
        err = UpdateModifyCapwapFragmenation(p_Manip, h_Ad, validate, h_FmTree);
        break;
#endif /* (defined(FM_CAPWAP_SUPPORT) && (DPAA_VERSION == 10)) */
        default:
            return E_OK;
    }

    return err;
}