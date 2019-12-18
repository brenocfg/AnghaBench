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
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  sched_pin () ; 
 int /*<<< orphan*/  sched_unpin () ; 

uint8_t
KfRaiseIrql(uint8_t irql)
{
	uint8_t			oldirql;

	sched_pin();
	oldirql = KeGetCurrentIrql();

	/* I am so going to hell for this. */
	if (oldirql > irql)
		panic("IRQL_NOT_LESS_THAN_OR_EQUAL");

	if (oldirql != DISPATCH_LEVEL) 
		mtx_lock(&disp_lock[curthread->td_oncpu]);
	else
		sched_unpin();	

/*printf("RAISE IRQL: %d %d\n", irql, oldirql);*/

	return (oldirql);
}