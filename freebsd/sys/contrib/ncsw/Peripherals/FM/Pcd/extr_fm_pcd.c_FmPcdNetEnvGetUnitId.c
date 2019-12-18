#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_12__ {TYPE_4__* netEnvs; } ;
typedef  TYPE_5__ t_FmPcd ;
typedef  scalar_t__ protocolOpt_t ;
typedef  scalar_t__ e_NetHeaderType ;
struct TYPE_11__ {TYPE_3__* aliasHdrs; TYPE_2__* units; } ;
struct TYPE_10__ {scalar_t__ hdr; scalar_t__ opt; size_t aliasHdr; } ;
struct TYPE_9__ {TYPE_1__* hdrs; } ;
struct TYPE_8__ {scalar_t__ hdr; scalar_t__ opt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_5__*) ; 
 size_t FM_PCD_MAX_NUM_OF_ALIAS_HDRS ; 
 size_t FM_PCD_MAX_NUM_OF_DISTINCTION_UNITS ; 
 size_t FM_PCD_MAX_NUM_OF_INTERCHANGEABLE_HDRS ; 
 scalar_t__ HEADER_TYPE_NONE ; 

uint8_t FmPcdNetEnvGetUnitId(t_FmPcd *p_FmPcd, uint8_t netEnvId, e_NetHeaderType hdr, bool interchangeable, protocolOpt_t opt)
{
    uint8_t     i, k;

    ASSERT_COND(p_FmPcd);

    if (interchangeable)
    {
        for (i=0; (i < FM_PCD_MAX_NUM_OF_DISTINCTION_UNITS) &&
                 (p_FmPcd->netEnvs[netEnvId].units[i].hdrs[0].hdr != HEADER_TYPE_NONE); i++)
        {
            for (k=0; (k < FM_PCD_MAX_NUM_OF_INTERCHANGEABLE_HDRS) &&
                     (p_FmPcd->netEnvs[netEnvId].units[i].hdrs[k].hdr != HEADER_TYPE_NONE); k++)
            {
                if ((p_FmPcd->netEnvs[netEnvId].units[i].hdrs[k].hdr == hdr) &&
                    (p_FmPcd->netEnvs[netEnvId].units[i].hdrs[k].opt == opt))

                return i;
            }
        }
    }
    else
    {
        for (i=0; (i < FM_PCD_MAX_NUM_OF_DISTINCTION_UNITS) &&
                 (p_FmPcd->netEnvs[netEnvId].units[i].hdrs[0].hdr != HEADER_TYPE_NONE); i++)
            if ((p_FmPcd->netEnvs[netEnvId].units[i].hdrs[0].hdr == hdr) &&
                (p_FmPcd->netEnvs[netEnvId].units[i].hdrs[0].opt == opt) &&
                (p_FmPcd->netEnvs[netEnvId].units[i].hdrs[1].hdr == HEADER_TYPE_NONE))
                    return i;

        for (i=0; (i < FM_PCD_MAX_NUM_OF_ALIAS_HDRS) &&
                 (p_FmPcd->netEnvs[netEnvId].aliasHdrs[i].hdr != HEADER_TYPE_NONE); i++)
            if ((p_FmPcd->netEnvs[netEnvId].aliasHdrs[i].hdr == hdr) &&
                (p_FmPcd->netEnvs[netEnvId].aliasHdrs[i].opt == opt))
                return p_FmPcd->netEnvs[netEnvId].aliasHdrs[i].aliasHdr;
    }

    return FM_PCD_MAX_NUM_OF_DISTINCTION_UNITS;
}