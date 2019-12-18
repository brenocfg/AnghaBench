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
struct TYPE_4__ {int /*<<< orphan*/  flag; } ;
typedef  TYPE_1__ t_FmPcdLock ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 

__attribute__((used)) static __inline__ void FmPcdLockUnlock(t_FmPcdLock *p_Lock)
{
    ASSERT_COND(p_Lock);
    p_Lock->flag = FALSE;
}