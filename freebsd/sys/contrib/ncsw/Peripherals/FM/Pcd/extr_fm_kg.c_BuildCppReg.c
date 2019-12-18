#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {TYPE_2__* p_FmPcdKg; } ;
typedef  TYPE_3__ t_FmPcd ;
struct TYPE_6__ {TYPE_1__* clsPlanGrps; } ;
struct TYPE_5__ {int baseEntry; int sizeOfGrp; } ;

/* Variables and functions */
 int FM_KG_PE_CPP_MASK_SHIFT ; 

__attribute__((used)) static uint32_t BuildCppReg(t_FmPcd *p_FmPcd, uint8_t clsPlanGrpId)
{
    uint32_t    tmpKgpeCpp;

    tmpKgpeCpp = (uint32_t)(p_FmPcd->p_FmPcdKg->clsPlanGrps[clsPlanGrpId].baseEntry / 8);
    tmpKgpeCpp |= (uint32_t)(((p_FmPcd->p_FmPcdKg->clsPlanGrps[clsPlanGrpId].sizeOfGrp / 8) - 1) << FM_KG_PE_CPP_MASK_SHIFT);

    return tmpKgpeCpp;
}