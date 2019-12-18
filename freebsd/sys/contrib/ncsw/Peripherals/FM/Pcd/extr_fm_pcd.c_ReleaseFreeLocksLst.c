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
struct TYPE_4__ {int /*<<< orphan*/  h_Spinlock; } ;
typedef  TYPE_1__ t_FmPcdLock ;
typedef  int /*<<< orphan*/  t_FmPcd ;

/* Variables and functions */
 TYPE_1__* DequeueLockFromFreeLst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XX_Free (TYPE_1__*) ; 
 int /*<<< orphan*/  XX_FreeSpinlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ReleaseFreeLocksLst(t_FmPcd *p_FmPcd)
{
    t_FmPcdLock *p_Lock;

    p_Lock = DequeueLockFromFreeLst(p_FmPcd);
    while (p_Lock)
    {
        XX_FreeSpinlock(p_Lock->h_Spinlock);
        XX_Free(p_Lock);
        p_Lock = DequeueLockFromFreeLst(p_FmPcd);
    }
}