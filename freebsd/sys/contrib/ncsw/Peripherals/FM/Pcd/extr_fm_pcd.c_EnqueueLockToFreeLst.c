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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ t_FmPcdLock ;
struct TYPE_6__ {int /*<<< orphan*/  h_Spinlock; int /*<<< orphan*/  freeLocksLst; } ;
typedef  TYPE_2__ t_FmPcd ;

/* Variables and functions */
 int /*<<< orphan*/  NCSW_LIST_AddToTail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XX_LockIntrSpinlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_UnlockIntrSpinlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void EnqueueLockToFreeLst(t_FmPcd *p_FmPcd, t_FmPcdLock *p_Lock)
{
    uint32_t   intFlags;

    intFlags = XX_LockIntrSpinlock(p_FmPcd->h_Spinlock);
    NCSW_LIST_AddToTail(&p_Lock->node, &p_FmPcd->freeLocksLst);
    XX_UnlockIntrSpinlock(p_FmPcd->h_Spinlock, intFlags);
}