#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  h_Spinlock; int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ t_FmPcdLock ;
typedef  int /*<<< orphan*/  t_FmPcd ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  EnqueueLockToFreeLst (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  INIT_LIST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MINOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XX_Free (TYPE_1__*) ; 
 int /*<<< orphan*/  XX_InitSpinlock () ; 
 scalar_t__ XX_Malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static t_Error FillFreeLocksLst(t_FmPcd *p_FmPcd)
{
    t_FmPcdLock *p_Lock;
    int         i;

    for (i=0; i<10; i++)
    {
        p_Lock = (t_FmPcdLock *)XX_Malloc(sizeof(t_FmPcdLock));
        if (!p_Lock)
            RETURN_ERROR(MINOR, E_NO_MEMORY, ("FM-PCD lock obj!"));
        memset(p_Lock, 0, sizeof(t_FmPcdLock));
        INIT_LIST(&p_Lock->node);
        p_Lock->h_Spinlock = XX_InitSpinlock();
        if (!p_Lock->h_Spinlock)
        {
            XX_Free(p_Lock);
            RETURN_ERROR(MINOR, E_INVALID_STATE, ("FM-PCD spinlock obj!"));
        }
        EnqueueLockToFreeLst(p_FmPcd, p_Lock);
    }

    return E_OK;
}