#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  TYPE_7__* t_Handle ;
struct TYPE_30__ {TYPE_7__* h_Ipv6Scheme; TYPE_7__* h_Ipv4Scheme; scalar_t__* relativeSchemeId; } ;
struct TYPE_31__ {TYPE_5__ ip; } ;
struct TYPE_32__ {TYPE_6__ reassmParams; } ;
typedef  TYPE_7__ t_FmPcdManip ;
struct TYPE_29__ {int hashDistributionNumOfFqids; } ;
struct TYPE_28__ {int update; } ;
struct TYPE_27__ {scalar_t__ relativeSchemeId; } ;
struct TYPE_26__ {TYPE_7__* h_NetEnv; } ;
struct TYPE_33__ {int alwaysDirect; int bypassFqidGeneration; int baseFqid; TYPE_4__ keyExtractAndHashParams; TYPE_3__ schemeCounter; TYPE_2__ id; TYPE_1__ netEnvParams; } ;
typedef  TYPE_9__ t_FmPcdKgSchemeParams ;
typedef  TYPE_7__ t_FmPcd ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_7__*) ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  E_OK ; 
 void* FM_PCD_KgSchemeSet (TYPE_7__*,TYPE_9__*) ; 
 TYPE_7__* FmPcdKgGetSchemeHandle (TYPE_7__*,scalar_t__) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int TRUE ; 
 int /*<<< orphan*/  XX_Free (TYPE_9__*) ; 
 TYPE_9__* XX_Malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setIpReassmSchemeParams (TYPE_7__*,TYPE_9__*,TYPE_7__*,int,scalar_t__) ; 

t_Error FmPcdManipBuildIpReassmScheme(t_FmPcd *p_FmPcd, t_Handle h_NetEnv,
                                      t_Handle h_CcTree, t_Handle h_Manip,
                                      bool isIpv4, uint8_t groupId)
{
    t_FmPcdManip *p_Manip = (t_FmPcdManip *)h_Manip;
    t_FmPcdKgSchemeParams *p_SchemeParams = NULL;
    t_Handle h_Scheme;

    ASSERT_COND(p_FmPcd);
    ASSERT_COND(h_NetEnv);
    ASSERT_COND(p_Manip);

    /* scheme was already build, no need to check for IPv6 */
    if (p_Manip->reassmParams.ip.h_Ipv4Scheme)
        return E_OK;

    if (isIpv4) {
        h_Scheme = FmPcdKgGetSchemeHandle(p_FmPcd, p_Manip->reassmParams.ip.relativeSchemeId[0]);
        if (h_Scheme) {
            /* scheme was found */
            p_Manip->reassmParams.ip.h_Ipv4Scheme = h_Scheme;
            return E_OK;
        }
    } else {
        h_Scheme = FmPcdKgGetSchemeHandle(p_FmPcd, p_Manip->reassmParams.ip.relativeSchemeId[1]);
        if (h_Scheme) {
            /* scheme was found */
            p_Manip->reassmParams.ip.h_Ipv6Scheme = h_Scheme;
            return E_OK;
        }
    }

     p_SchemeParams = XX_Malloc(sizeof(t_FmPcdKgSchemeParams));
    if (!p_SchemeParams)
        RETURN_ERROR(MAJOR, E_NO_MEMORY,
                     ("Memory allocation failed for scheme"));

    /* Configures the IPv4 or IPv6 scheme*/
    memset(p_SchemeParams, 0, sizeof(t_FmPcdKgSchemeParams));
    p_SchemeParams->netEnvParams.h_NetEnv = h_NetEnv;
    p_SchemeParams->id.relativeSchemeId = (uint8_t)(
            (isIpv4 == TRUE) ? p_Manip->reassmParams.ip.relativeSchemeId[0] :
                    p_Manip->reassmParams.ip.relativeSchemeId[1]);
    p_SchemeParams->schemeCounter.update = TRUE;
#if (DPAA_VERSION >= 11)
    p_SchemeParams->alwaysDirect = TRUE;
    p_SchemeParams->bypassFqidGeneration = TRUE;
#else
    p_SchemeParams->keyExtractAndHashParams.hashDistributionNumOfFqids = 1;
    p_SchemeParams->baseFqid = 0xFFFFFF; /*TODO- baseFqid*/
#endif /* (DPAA_VERSION >= 11) */

    setIpReassmSchemeParams(p_FmPcd, p_SchemeParams, h_CcTree, isIpv4, groupId);

    /* Sets the new scheme */
    if (isIpv4)
        p_Manip->reassmParams.ip.h_Ipv4Scheme = FM_PCD_KgSchemeSet(
                p_FmPcd, p_SchemeParams);
    else
        p_Manip->reassmParams.ip.h_Ipv6Scheme = FM_PCD_KgSchemeSet(
                p_FmPcd, p_SchemeParams);

    XX_Free(p_SchemeParams);

    return E_OK;
}