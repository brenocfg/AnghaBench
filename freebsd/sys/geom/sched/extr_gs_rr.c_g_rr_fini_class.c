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
struct g_rr_queue {TYPE_1__* q_sc; int /*<<< orphan*/  q_bioq; } ;
struct TYPE_4__ {int /*<<< orphan*/  queues; } ;
struct TYPE_3__ {int /*<<< orphan*/  sc_nqueues; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * bioq_first (int /*<<< orphan*/ *) ; 
 TYPE_2__ me ; 

__attribute__((used)) static void
g_rr_fini_class(void *data, void *priv)
{
	struct g_rr_queue *qp = priv;

	KASSERT(bioq_first(&qp->q_bioq) == NULL,
			("released nonempty queue"));
	qp->q_sc->sc_nqueues--;
	me.queues--;
}