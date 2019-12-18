#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  t_FmPcd ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  BuildCppReg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KgWriteCpp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static t_Error BindPortToClsPlanGrp(t_FmPcd *p_FmPcd, uint8_t hardwarePortId, uint8_t clsPlanGrpId)
{
    uint32_t                tmpKgpeCpp = 0;

    tmpKgpeCpp = BuildCppReg(p_FmPcd, clsPlanGrpId);
    return KgWriteCpp(p_FmPcd, hardwarePortId, tmpKgpeCpp);
}