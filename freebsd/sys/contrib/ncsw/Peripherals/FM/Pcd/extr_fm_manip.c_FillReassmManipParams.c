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
typedef  int uint32_t ;
struct TYPE_10__ {scalar_t__ nonConsistentSpFqid; int /*<<< orphan*/  p_Ipv6ReassTbl; scalar_t__ h_Ipv6Ad; int /*<<< orphan*/  p_Ipv4ReassTbl; scalar_t__ h_Ipv4Ad; } ;
struct TYPE_9__ {int /*<<< orphan*/  p_ReassTbl; scalar_t__ h_Ad; } ;
struct TYPE_11__ {int sgBpid; TYPE_2__ ip; TYPE_1__ capwap; } ;
struct TYPE_12__ {int updateParams; int /*<<< orphan*/  reassm; TYPE_3__ reassmParams; scalar_t__ h_FmPcd; } ;
typedef  TYPE_4__ t_FmPcdManip ;
struct TYPE_13__ {scalar_t__ physicalMuramBase; } ;
typedef  TYPE_5__ t_FmPcd ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_14__ {int /*<<< orphan*/  pcAndOffsets; int /*<<< orphan*/  gmask; int /*<<< orphan*/  matchTblPtr; int /*<<< orphan*/  ccAdBase; } ;
typedef  TYPE_6__ t_AdOfTypeContLookup ;
typedef  int e_NetHeaderType ;

/* Variables and functions */
 int /*<<< orphan*/  CreateReassTable (TYPE_4__*,int) ; 
 int DISCARD_MASK ; 
 int /*<<< orphan*/  E_NOT_SUPPORTED ; 
 int /*<<< orphan*/  E_OK ; 
 int FM_PCD_AD_CONT_LOOKUP_TYPE ; 
 int FM_PCD_AD_NCSPFQIDM_MASK ; 
#define  HEADER_TYPE_CAPWAP 130 
#define  HEADER_TYPE_IPv4 129 
#define  HEADER_TYPE_IPv6 128 
 scalar_t__ HMAN_OC_CAPWAP_REASSEMBLY ; 
 scalar_t__ HMAN_OC_IP_REASSEMBLY ; 
 int /*<<< orphan*/  MAJOR ; 
 char* NO_MSG ; 
 int NUM_OF_EXTRA_TASKS ; 
 int NUM_OF_TASKS ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ XX_VirtToPhys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static t_Error FillReassmManipParams(t_FmPcdManip *p_Manip, e_NetHeaderType hdr)
{
    t_AdOfTypeContLookup *p_Ad;
    t_FmPcd *p_FmPcd = (t_FmPcd *)p_Manip->h_FmPcd;
    uint32_t tmpReg32;
    t_Error err = E_OK;

    /* Creates the Reassembly Parameters table. It contains parameters that are specific to either the IPv4 reassembly
     function or to the IPv6 reassembly function. If both IPv4 reassembly and IPv6 reassembly are required, then
     two separate IP Reassembly Parameter tables are required.*/
    if ((err = CreateReassTable(p_Manip, hdr)) != E_OK)
        RETURN_ERROR(MAJOR, err, NO_MSG);

    /* Sets the first Ad register (ccAdBase) - Action Descriptor Type and Pointer to the Reassembly Parameters Table offset from MURAM*/
    tmpReg32 = 0;
    tmpReg32 |= FM_PCD_AD_CONT_LOOKUP_TYPE;

    /* Gets the required Action descriptor table pointer */
    switch (hdr)
    {
        case HEADER_TYPE_IPv4:
            p_Ad = (t_AdOfTypeContLookup *)p_Manip->reassmParams.ip.h_Ipv4Ad;
            tmpReg32 |= (uint32_t)(XX_VirtToPhys(
                    p_Manip->reassmParams.ip.p_Ipv4ReassTbl)
                    - (p_FmPcd->physicalMuramBase));
            break;
        case HEADER_TYPE_IPv6:
            p_Ad = (t_AdOfTypeContLookup *)p_Manip->reassmParams.ip.h_Ipv6Ad;
            tmpReg32 |= (uint32_t)(XX_VirtToPhys(
                    p_Manip->reassmParams.ip.p_Ipv6ReassTbl)
                    - (p_FmPcd->physicalMuramBase));
            break;
        case HEADER_TYPE_CAPWAP:
            p_Ad = (t_AdOfTypeContLookup *)p_Manip->reassmParams.capwap.h_Ad;
            tmpReg32 |= (uint32_t)(XX_VirtToPhys(
                    p_Manip->reassmParams.capwap.p_ReassTbl)
                    - (p_FmPcd->physicalMuramBase));
            break;
        default:
            RETURN_ERROR(MAJOR, E_NOT_SUPPORTED, ("header type"));
    }

    WRITE_UINT32(p_Ad->ccAdBase, tmpReg32);

    /* Sets the second Ad register (matchTblPtr) - Buffer pool ID (BPID for V2) and Scatter/Gather table offset*/
    /* mark the Scatter/Gather table offset to be set later on when the port will be known */
    p_Manip->updateParams = (NUM_OF_TASKS | NUM_OF_EXTRA_TASKS | DISCARD_MASK);

    if ((hdr == HEADER_TYPE_IPv6) || (hdr == HEADER_TYPE_IPv4))
    {
#if (DPAA_VERSION == 10)
        tmpReg32 = (uint32_t)(p_Manip->reassmParams.sgBpid << 8);
        WRITE_UINT32(p_Ad->matchTblPtr, tmpReg32);
#endif /* (DPAA_VERSION == 10) */
#if (DPAA_VERSION >= 11)
        if (p_Manip->reassmParams.ip.nonConsistentSpFqid != 0)
        {
            tmpReg32 = FM_PCD_AD_NCSPFQIDM_MASK
                    | (uint32_t)(p_Manip->reassmParams.ip.nonConsistentSpFqid);
            WRITE_UINT32(p_Ad->gmask, tmpReg32);
        }
#endif /* (DPAA_VERSION >= 11) */
        /* Sets the third Ad register (pcAndOffsets)- IP Reassemble Operation Code*/
        tmpReg32 = 0;
        tmpReg32 |= (uint32_t)HMAN_OC_IP_REASSEMBLY;
    }
#if (DPAA_VERSION >= 11)
    else
        if (hdr == HEADER_TYPE_CAPWAP)
        {
            tmpReg32 = 0;
            tmpReg32 |= (uint32_t)HMAN_OC_CAPWAP_REASSEMBLY;
        }
#endif /* (DPAA_VERSION >= 11) */

    WRITE_UINT32(p_Ad->pcAndOffsets, tmpReg32);

    p_Manip->reassm = TRUE;

    return E_OK;
}