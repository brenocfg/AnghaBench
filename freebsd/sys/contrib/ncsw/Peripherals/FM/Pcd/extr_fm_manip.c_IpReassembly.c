#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_17__ {int timeoutThresholdForReassmProcess; int maxNumFramesInProcess; int* minFragSize; scalar_t__ nonConsistentSpFqid; int /*<<< orphan*/  sgBpid; int /*<<< orphan*/  dataLiodnOffset; int /*<<< orphan*/  dataMemId; int /*<<< orphan*/  fqidForTimeOutFrames; int /*<<< orphan*/  timeOutMode; int /*<<< orphan*/ * numOfFramesPerHashEntry; int /*<<< orphan*/ * relativeSchemeId; } ;
struct TYPE_13__ {TYPE_5__ ipReassem; } ;
struct TYPE_16__ {scalar_t__ hdr; TYPE_1__ u; } ;
typedef  TYPE_4__ t_FmPcdManipReassemParams ;
typedef  TYPE_5__ t_FmPcdManipReassemIpParams ;
struct TYPE_14__ {int* minFragSize; scalar_t__ nonConsistentSpFqid; int /*<<< orphan*/ * numOfFramesPerHashEntry; int /*<<< orphan*/ * relativeSchemeId; } ;
struct TYPE_15__ {int maxNumFramesInProcess; int timeoutThresholdForReassmProcess; scalar_t__ hdr; TYPE_2__ ip; int /*<<< orphan*/  sgBpid; int /*<<< orphan*/  dataLiodnOffset; int /*<<< orphan*/  dataMemId; int /*<<< orphan*/  fqidForTimeOutFrames; int /*<<< orphan*/  timeOutMode; } ;
struct TYPE_18__ {TYPE_3__ reassmParams; scalar_t__ h_FmPcd; } ;
typedef  TYPE_6__ t_FmPcdManip ;
struct TYPE_19__ {scalar_t__ h_Hc; } ;
typedef  TYPE_7__ t_FmPcd ;
typedef  scalar_t__ t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  CreateReassCommonTable (TYPE_6__*) ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 scalar_t__ E_OK ; 
 scalar_t__ HEADER_TYPE_IPv4 ; 
 scalar_t__ HEADER_TYPE_IPv6 ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SetIpv4ReassmManip (TYPE_6__*) ; 
 scalar_t__ SetIpv6ReassmManip (TYPE_6__*) ; 

__attribute__((used)) static t_Error IpReassembly(t_FmPcdManipReassemParams *p_ManipReassmParams,
                            t_FmPcdManip *p_Manip)
{
    uint32_t maxSetNumber = 10000;
    t_FmPcdManipReassemIpParams reassmManipParams =
            p_ManipReassmParams->u.ipReassem;
    t_Error res;

    SANITY_CHECK_RETURN_ERROR(p_Manip->h_FmPcd, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(((t_FmPcd *)p_Manip->h_FmPcd)->h_Hc,
                              E_INVALID_HANDLE);

    /* Check validation of user's parameter.*/
    if ((reassmManipParams.timeoutThresholdForReassmProcess < 1000)
            || (reassmManipParams.timeoutThresholdForReassmProcess > 8000000))
        RETURN_ERROR(
                MAJOR, E_INVALID_VALUE,
                ("timeoutThresholdForReassmProcess should be 1msec - 8sec"));
    /* It is recommended that the total number of entries in this table (number of sets * number of ways)
     will be twice the number of frames that are expected to be reassembled simultaneously.*/
    if (reassmManipParams.maxNumFramesInProcess
            > (reassmManipParams.maxNumFramesInProcess * maxSetNumber / 2))
        RETURN_ERROR(
                MAJOR,
                E_INVALID_VALUE,
                ("maxNumFramesInProcess has to be less than (maximun set number * number of ways / 2)"));

    if ((p_ManipReassmParams->hdr == HEADER_TYPE_IPv6)
            && (reassmManipParams.minFragSize[1] < 256))
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("minFragSize[1] must be >= 256"));

    /* Saves user's reassembly manipulation parameters */
    p_Manip->reassmParams.ip.relativeSchemeId[0] =
            reassmManipParams.relativeSchemeId[0];
    p_Manip->reassmParams.ip.relativeSchemeId[1] =
            reassmManipParams.relativeSchemeId[1];
    p_Manip->reassmParams.ip.numOfFramesPerHashEntry[0] =
            reassmManipParams.numOfFramesPerHashEntry[0];
    p_Manip->reassmParams.ip.numOfFramesPerHashEntry[1] =
            reassmManipParams.numOfFramesPerHashEntry[1];
    p_Manip->reassmParams.ip.minFragSize[0] = reassmManipParams.minFragSize[0];
    p_Manip->reassmParams.ip.minFragSize[1] = reassmManipParams.minFragSize[1];
    p_Manip->reassmParams.maxNumFramesInProcess =
            reassmManipParams.maxNumFramesInProcess;
    p_Manip->reassmParams.timeOutMode = reassmManipParams.timeOutMode;
    p_Manip->reassmParams.fqidForTimeOutFrames =
            reassmManipParams.fqidForTimeOutFrames;
    p_Manip->reassmParams.timeoutThresholdForReassmProcess =
            reassmManipParams.timeoutThresholdForReassmProcess;
    p_Manip->reassmParams.dataMemId = reassmManipParams.dataMemId;
    p_Manip->reassmParams.dataLiodnOffset = reassmManipParams.dataLiodnOffset;
#if (DPAA_VERSION == 10)
    p_Manip->reassmParams.sgBpid = reassmManipParams.sgBpid;
#endif /* (DPAA_VERSION == 10) */
#if (DPAA_VERSION >= 11)
    if (reassmManipParams.nonConsistentSpFqid != 0)
    {
        p_Manip->reassmParams.ip.nonConsistentSpFqid =
                reassmManipParams.nonConsistentSpFqid;
    }
#endif /* (DPAA_VERSION >= 11) */

    /* Creates and initializes the IP Reassembly common parameter table */
    CreateReassCommonTable(p_Manip);

    /* Creation of IPv4 reassembly manipulation */
    if ((p_Manip->reassmParams.hdr == HEADER_TYPE_IPv6)
            || (p_Manip->reassmParams.hdr == HEADER_TYPE_IPv4))
    {
        res = SetIpv4ReassmManip(p_Manip);
        if (res != E_OK)
            return res;
    }

    /* Creation of IPv6 reassembly manipulation */
    if (p_Manip->reassmParams.hdr == HEADER_TYPE_IPv6)
    {
        res = SetIpv6ReassmManip(p_Manip);
        if (res != E_OK)
            return res;
    }

    return E_OK;
}