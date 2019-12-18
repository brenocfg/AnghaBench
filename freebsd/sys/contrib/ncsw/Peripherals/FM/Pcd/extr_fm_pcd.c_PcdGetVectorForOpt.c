#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_10__ {TYPE_3__* netEnvs; } ;
typedef  TYPE_4__ t_FmPcd ;
typedef  int /*<<< orphan*/  t_Error ;
typedef  scalar_t__ protocolOpt_t ;
struct TYPE_9__ {int /*<<< orphan*/ * unitsVectors; TYPE_2__* units; } ;
struct TYPE_8__ {TYPE_1__* hdrs; } ;
struct TYPE_7__ {scalar_t__ hdr; scalar_t__ opt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_4__*) ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_OK ; 
 size_t FM_PCD_MAX_NUM_OF_DISTINCTION_UNITS ; 
 size_t FM_PCD_MAX_NUM_OF_INTERCHANGEABLE_HDRS ; 
 scalar_t__ HEADER_TYPE_NONE ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

t_Error PcdGetVectorForOpt(t_FmPcd *p_FmPcd, uint8_t netEnvId, protocolOpt_t opt, uint32_t *p_Vector)
{
    uint8_t     j,k;

    *p_Vector = 0;

    ASSERT_COND(p_FmPcd);
    for (j=0; ((j < FM_PCD_MAX_NUM_OF_DISTINCTION_UNITS) &&
              (p_FmPcd->netEnvs[netEnvId].units[j].hdrs[0].hdr != HEADER_TYPE_NONE)); j++)
    {
        for (k=0; ((k < FM_PCD_MAX_NUM_OF_INTERCHANGEABLE_HDRS) &&
                  (p_FmPcd->netEnvs[netEnvId].units[j].hdrs[k].hdr != HEADER_TYPE_NONE)); k++)
        {
            if (p_FmPcd->netEnvs[netEnvId].units[j].hdrs[k].opt == opt)
                *p_Vector |= p_FmPcd->netEnvs[netEnvId].unitsVectors[j];
        }
    }

    if (!*p_Vector)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("Requested option was not defined for this Network Environment Characteristics module"));
    else
        return E_OK;
}