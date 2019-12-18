#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int th_txg; TYPE_2__* th_cpu; } ;
typedef  TYPE_1__ txg_handle_t ;
struct TYPE_5__ {scalar_t__* tc_count; int /*<<< orphan*/  tc_lock; int /*<<< orphan*/ * tc_cv; } ;
typedef  TYPE_2__ tx_cpu_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int TXG_MASK ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
txg_rele_to_sync(txg_handle_t *th)
{
	tx_cpu_t *tc = th->th_cpu;
	int g = th->th_txg & TXG_MASK;

	mutex_enter(&tc->tc_lock);
	ASSERT(tc->tc_count[g] != 0);
	if (--tc->tc_count[g] == 0)
		cv_broadcast(&tc->tc_cv[g]);
	mutex_exit(&tc->tc_lock);

	th->th_cpu = NULL;	/* defensive */
}