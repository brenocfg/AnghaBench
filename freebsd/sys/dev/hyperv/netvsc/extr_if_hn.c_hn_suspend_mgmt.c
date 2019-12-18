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
struct task {int dummy; } ;
struct hn_softc {int /*<<< orphan*/  hn_mgmt_taskq0; int /*<<< orphan*/  hn_netchg_status; int /*<<< orphan*/  hn_netchg_init; int /*<<< orphan*/  hn_prichan; } ;

/* Variables and functions */
 int /*<<< orphan*/  HN_LOCK_ASSERT (struct hn_softc*) ; 
 int /*<<< orphan*/  TASK_INIT (struct task*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hn_softc*) ; 
 int /*<<< orphan*/  hn_suspend_mgmt_taskfunc ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_drain_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_chan_run_task (int /*<<< orphan*/ ,struct task*) ; 

__attribute__((used)) static void
hn_suspend_mgmt(struct hn_softc *sc)
{
	struct task task;

	HN_LOCK_ASSERT(sc);

	/*
	 * Make sure that hn_mgmt_taskq0 can nolonger be accessed
	 * through hn_mgmt_taskq.
	 */
	TASK_INIT(&task, 0, hn_suspend_mgmt_taskfunc, sc);
	vmbus_chan_run_task(sc->hn_prichan, &task);

	/*
	 * Make sure that all pending management tasks are completed.
	 */
	taskqueue_drain(sc->hn_mgmt_taskq0, &sc->hn_netchg_init);
	taskqueue_drain_timeout(sc->hn_mgmt_taskq0, &sc->hn_netchg_status);
	taskqueue_drain_all(sc->hn_mgmt_taskq0);
}