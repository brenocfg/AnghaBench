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
struct TYPE_5__ {int /*<<< orphan*/  slow_intr_task; int /*<<< orphan*/  sge_timer_ch; } ;
typedef  TYPE_1__ adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TX_RECLAIM_PERIOD ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sge_slow_intr_handler ; 
 int /*<<< orphan*/  sge_timer_cb ; 

int
t3_sge_init_adapter(adapter_t *sc)
{
	callout_init(&sc->sge_timer_ch, 1);
	callout_reset(&sc->sge_timer_ch, TX_RECLAIM_PERIOD, sge_timer_cb, sc);
	TASK_INIT(&sc->slow_intr_task, 0, sge_slow_intr_handler, sc);
	return (0);
}