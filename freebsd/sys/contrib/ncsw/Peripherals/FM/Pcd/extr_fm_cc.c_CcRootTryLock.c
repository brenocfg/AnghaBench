#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_Handle ;
struct TYPE_2__ {int /*<<< orphan*/  p_Lock; } ;
typedef  TYPE_1__ t_FmPcdCcTree ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (scalar_t__) ; 
 int /*<<< orphan*/  ERROR_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_BUSY ; 
 int /*<<< orphan*/  E_OK ; 
 scalar_t__ FmPcdLockTryLock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static t_Error CcRootTryLock(t_Handle h_FmPcdCcTree)
{
    t_FmPcdCcTree *p_FmPcdCcTree = (t_FmPcdCcTree *)h_FmPcdCcTree;

    ASSERT_COND(h_FmPcdCcTree);

    if (FmPcdLockTryLock(p_FmPcdCcTree->p_Lock))
        return E_OK;

    return ERROR_CODE(E_BUSY);
}