#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_6__ {TYPE_1__* netEnvs; } ;
typedef  TYPE_2__ t_FmPcd ;
struct TYPE_5__ {size_t clsPlanGrpId; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_2__*) ; 

void FmPcdSetClsPlanGrpId(t_FmPcd *p_FmPcd, uint8_t netEnvId, uint8_t clsPlanGrpId)
{
    ASSERT_COND(p_FmPcd);
    p_FmPcd->netEnvs[netEnvId].clsPlanGrpId = clsPlanGrpId;
}