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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {size_t td_oncpu; } ;

/* Variables and functions */
 scalar_t__ DISPATCH_LEVEL ; 
 scalar_t__ KeGetCurrentIrql () ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/ * disp_lock ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  sched_unpin () ; 

void
KfLowerIrql(uint8_t oldirql)
{
	if (oldirql == DISPATCH_LEVEL)
		return;

	if (KeGetCurrentIrql() != DISPATCH_LEVEL)
		panic("IRQL_NOT_GREATER_THAN");

	mtx_unlock(&disp_lock[curthread->td_oncpu]);
	sched_unpin();
}