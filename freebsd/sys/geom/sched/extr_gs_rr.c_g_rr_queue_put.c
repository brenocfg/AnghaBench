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
struct g_rr_queue {TYPE_1__* q_sc; } ;
struct TYPE_2__ {int /*<<< orphan*/  sc_geom; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_sched_put_class (int /*<<< orphan*/ ,struct g_rr_queue*) ; 

__attribute__((used)) static void
g_rr_queue_put(struct g_rr_queue *qp)
{

	g_sched_put_class(qp->q_sc->sc_geom, qp);
}