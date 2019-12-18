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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_2__ {int /*<<< orphan*/  h_Spinlock; } ;
typedef  TYPE_1__ t_FmPcdNetEnv ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (scalar_t__) ; 
 int /*<<< orphan*/  XX_LockIntrSpinlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t NetEnvLock(t_Handle h_NetEnv)
{
    ASSERT_COND(h_NetEnv);
    return XX_LockIntrSpinlock(((t_FmPcdNetEnv*)h_NetEnv)->h_Spinlock);
}