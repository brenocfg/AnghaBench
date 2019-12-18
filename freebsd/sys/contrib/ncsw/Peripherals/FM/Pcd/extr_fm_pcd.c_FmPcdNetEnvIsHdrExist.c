#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_11__ {TYPE_4__* netEnvs; } ;
typedef  TYPE_5__ t_FmPcd ;
typedef  scalar_t__ e_NetHeaderType ;
struct TYPE_10__ {TYPE_3__* aliasHdrs; TYPE_2__* units; } ;
struct TYPE_9__ {scalar_t__ hdr; } ;
struct TYPE_8__ {TYPE_1__* hdrs; } ;
struct TYPE_7__ {scalar_t__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_5__*) ; 
 int FALSE ; 
 int FM_PCD_MAX_NUM_OF_ALIAS_HDRS ; 
 int FM_PCD_MAX_NUM_OF_DISTINCTION_UNITS ; 
 int FM_PCD_MAX_NUM_OF_INTERCHANGEABLE_HDRS ; 
 scalar_t__ HEADER_TYPE_NONE ; 
 int TRUE ; 

bool  FmPcdNetEnvIsHdrExist(t_Handle h_FmPcd, uint8_t netEnvId, e_NetHeaderType hdr)
{
    t_FmPcd     *p_FmPcd = (t_FmPcd*)h_FmPcd;
    int         i, k;

    ASSERT_COND(p_FmPcd);

    for (i=0; ((i < FM_PCD_MAX_NUM_OF_DISTINCTION_UNITS) &&
              (p_FmPcd->netEnvs[netEnvId].units[i].hdrs[0].hdr != HEADER_TYPE_NONE)); i++)
    {
        for (k=0; ((k < FM_PCD_MAX_NUM_OF_INTERCHANGEABLE_HDRS) &&
                  (p_FmPcd->netEnvs[netEnvId].units[i].hdrs[k].hdr != HEADER_TYPE_NONE)); k++)
            if (p_FmPcd->netEnvs[netEnvId].units[i].hdrs[k].hdr == hdr)
                return TRUE;
    }
    for (i=0; ((i < FM_PCD_MAX_NUM_OF_ALIAS_HDRS) &&
              (p_FmPcd->netEnvs[netEnvId].aliasHdrs[i].hdr != HEADER_TYPE_NONE)); i++)
    {
        if (p_FmPcd->netEnvs[netEnvId].aliasHdrs[i].hdr == hdr)
            return TRUE;
    }

    return FALSE;
}