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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct socket {int so_state; int /*<<< orphan*/ * so_sigio; int /*<<< orphan*/  sol_comp; TYPE_1__ so_rdsel; int /*<<< orphan*/  sol_upcallarg; int /*<<< orphan*/  (* sol_upcall ) (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KNOTE_LOCKED (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PSOCK ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  SOLISTEN_UNLOCK (struct socket*) ; 
 int SS_ASYNC ; 
 int /*<<< orphan*/  pgsigio (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selwakeuppri (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup_one (int /*<<< orphan*/ *) ; 

void
solisten_wakeup(struct socket *sol)
{

	if (sol->sol_upcall != NULL)
		(void )sol->sol_upcall(sol, sol->sol_upcallarg, M_NOWAIT);
	else {
		selwakeuppri(&sol->so_rdsel, PSOCK);
		KNOTE_LOCKED(&sol->so_rdsel.si_note, 0);
	}
	SOLISTEN_UNLOCK(sol);
	wakeup_one(&sol->sol_comp);
	if ((sol->so_state & SS_ASYNC) && sol->so_sigio != NULL)
		pgsigio(&sol->so_sigio, SIGIO, 0);
}