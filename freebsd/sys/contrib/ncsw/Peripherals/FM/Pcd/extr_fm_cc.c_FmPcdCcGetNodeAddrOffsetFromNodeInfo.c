#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_4__ {scalar_t__ physicalMuramBase; } ;
typedef  TYPE_1__ t_FmPcd ;
struct TYPE_5__ {int /*<<< orphan*/  h_CcNode; } ;
typedef  TYPE_2__ t_CcNodeInformation ;

/* Variables and functions */
 TYPE_2__* CC_NODE_F_OBJECT (scalar_t__) ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 scalar_t__ ILLEGAL_BASE ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_VALUE (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XX_VirtToPhys (int /*<<< orphan*/ ) ; 

uint32_t FmPcdCcGetNodeAddrOffsetFromNodeInfo(t_Handle h_FmPcd,
                                              t_Handle h_Pointer)
{
    t_FmPcd *p_FmPcd = (t_FmPcd *)h_FmPcd;
    t_CcNodeInformation *p_CcNodeInfo;

    SANITY_CHECK_RETURN_VALUE(h_FmPcd, E_INVALID_HANDLE,
                              (uint32_t)ILLEGAL_BASE);

    p_CcNodeInfo = CC_NODE_F_OBJECT(h_Pointer);

    return (uint32_t)(XX_VirtToPhys(p_CcNodeInfo->h_CcNode)
            - p_FmPcd->physicalMuramBase);
}