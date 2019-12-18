#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct g_rr_queue {void* q_lastsub; int q_bionum; int /*<<< orphan*/  q_thinktime; TYPE_1__* q_sc; } ;
struct TYPE_4__ {int /*<<< orphan*/  wait_ms; } ;
struct TYPE_3__ {struct g_rr_queue* sc_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_savg_add_sample (int /*<<< orphan*/ *,int) ; 
 int get_bounded (int /*<<< orphan*/ *,int) ; 
 TYPE_2__ me ; 
 void* ticks ; 

__attribute__((used)) static inline void
g_rr_update_thinktime(struct g_rr_queue *qp)
{
	int delta = ticks - qp->q_lastsub, wait = get_bounded(&me.wait_ms, 2);

	if (qp->q_sc->sc_active != qp)
		return;

	qp->q_lastsub = ticks;
	delta = (delta > 2 * wait) ? 2 * wait : delta;
	if (qp->q_bionum > 7)
		g_savg_add_sample(&qp->q_thinktime, delta);
}