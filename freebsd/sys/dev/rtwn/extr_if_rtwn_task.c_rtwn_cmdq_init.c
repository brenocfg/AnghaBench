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
struct rtwn_softc {int /*<<< orphan*/  cmdq_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTWN_CMDQ_LOCK_INIT (struct rtwn_softc*) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_cmdq_cb ; 

void
rtwn_cmdq_init(struct rtwn_softc *sc)
{
	RTWN_CMDQ_LOCK_INIT(sc);
	TASK_INIT(&sc->cmdq_task, 0, rtwn_cmdq_cb, sc);
}