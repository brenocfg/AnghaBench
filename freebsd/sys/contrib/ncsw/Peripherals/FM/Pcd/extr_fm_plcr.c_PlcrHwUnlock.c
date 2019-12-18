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
struct TYPE_2__ {int /*<<< orphan*/  h_HwSpinlock; } ;
typedef  TYPE_1__ t_FmPcdPlcr ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (scalar_t__) ; 
 int /*<<< orphan*/  XX_UnlockIntrSpinlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PlcrHwUnlock(t_Handle h_FmPcdPlcr, uint32_t intFlags)
{
    ASSERT_COND(h_FmPcdPlcr);
    XX_UnlockIntrSpinlock(((t_FmPcdPlcr*)h_FmPcdPlcr)->h_HwSpinlock, intFlags);
}