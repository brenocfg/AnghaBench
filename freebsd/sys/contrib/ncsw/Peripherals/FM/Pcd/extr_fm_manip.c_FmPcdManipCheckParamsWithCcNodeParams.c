#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
struct TYPE_2__ {int opcode; int /*<<< orphan*/  ownerTmp; int /*<<< orphan*/  h_Frag; } ;
typedef  TYPE_1__ t_FmPcdManip ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  FmPcdCcGetNumOfKeys (scalar_t__) ; 
 int /*<<< orphan*/  FmPcdCcGetOffset (scalar_t__) ; 
 int HMAN_OC_CAPWAP_INDEXED_STATS ; 
 int HMAN_OC_CAPWAP_RMV_DTLS_IF_EXIST ; 
 int /*<<< orphan*/  MAJOR ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateManipIc (scalar_t__,int /*<<< orphan*/ ) ; 

t_Error FmPcdManipCheckParamsWithCcNodeParams(t_Handle h_Manip,
                                              t_Handle h_FmPcdCcNode)
{
    t_FmPcdManip *p_Manip = (t_FmPcdManip *)h_Manip;
    t_Error err = E_OK;

    SANITY_CHECK_RETURN_ERROR(h_Manip, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(h_FmPcdCcNode, E_INVALID_HANDLE);

    switch (p_Manip->opcode)
    {
#if (defined(FM_CAPWAP_SUPPORT) && (DPAA_VERSION == 10))
        case (HMAN_OC_CAPWAP_INDEXED_STATS):
        if (p_Manip->ownerTmp != FmPcdCcGetNumOfKeys(h_FmPcdCcNode))
        RETURN_ERROR(
                MAJOR,
                E_INVALID_VALUE,
                ("The manipulation of the type statistics flowId if exist has to be pointed by all numOfKeys"));
        break;
        case (HMAN_OC_CAPWAP_RMV_DTLS_IF_EXIST):
        if (p_Manip->h_Frag)
        {
            if (p_Manip->ownerTmp != FmPcdCcGetNumOfKeys(h_FmPcdCcNode))
            RETURN_ERROR(
                    MAJOR,
                    E_INVALID_VALUE,
                    ("The manipulation of the type remove DTLS if exist has to be pointed by all numOfKeys"));
            err = UpdateManipIc(h_Manip, FmPcdCcGetOffset(h_FmPcdCcNode));
            if (err)
            RETURN_ERROR(MAJOR, err, NO_MSG);
        }
        break;
#endif /* (defined(FM_CAPWAP_SUPPORT) && (DPAA_VERSION == 10)) */
        default:
            break;
    }

    return err;
}