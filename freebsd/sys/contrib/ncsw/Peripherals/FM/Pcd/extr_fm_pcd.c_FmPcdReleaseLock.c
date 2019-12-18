#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_4__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ t_FmPcdLock ;
typedef  int /*<<< orphan*/  t_FmPcd ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (scalar_t__) ; 
 int /*<<< orphan*/  EnqueueLockToFreeLst (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  FmPcdLock (scalar_t__) ; 
 int /*<<< orphan*/  FmPcdUnlock (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NCSW_LIST_DelAndInit (int /*<<< orphan*/ *) ; 

void FmPcdReleaseLock(t_Handle h_FmPcd, t_FmPcdLock *p_Lock)
{
    uint32_t intFlags;
    ASSERT_COND(h_FmPcd);
    intFlags = FmPcdLock(h_FmPcd);
    NCSW_LIST_DelAndInit(&p_Lock->node);
    FmPcdUnlock(h_FmPcd, intFlags);
    EnqueueLockToFreeLst((t_FmPcd*)h_FmPcd, p_Lock);
}