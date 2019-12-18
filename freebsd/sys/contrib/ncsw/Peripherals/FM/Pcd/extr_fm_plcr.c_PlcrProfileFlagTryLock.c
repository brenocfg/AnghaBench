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
typedef  TYPE_1__ t_FmPcdPlcrProfile ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (scalar_t__) ; 
 int FmPcdLockTryLock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool PlcrProfileFlagTryLock(t_Handle h_Profile)
{
    ASSERT_COND(h_Profile);
    return FmPcdLockTryLock(((t_FmPcdPlcrProfile *)h_Profile)->p_Lock);
}