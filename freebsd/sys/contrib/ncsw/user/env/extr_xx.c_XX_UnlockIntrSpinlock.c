#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  t_Handle ;

/* Variables and functions */
 int /*<<< orphan*/  XX_UnlockSpinlock (int /*<<< orphan*/ ) ; 

void
XX_UnlockIntrSpinlock(t_Handle h_Spinlock, uint32_t intrFlags)
{

	XX_UnlockSpinlock(h_Spinlock);
}