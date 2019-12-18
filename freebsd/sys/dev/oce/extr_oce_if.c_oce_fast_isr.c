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
struct TYPE_4__ {TYPE_1__* eq; int /*<<< orphan*/  task; int /*<<< orphan*/  tq; int /*<<< orphan*/  sc; } ;
struct TYPE_3__ {int /*<<< orphan*/  intr; int /*<<< orphan*/  eq_id; } ;
typedef  int /*<<< orphan*/  POCE_SOFTC ;
typedef  TYPE_2__* POCE_INTR_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int FILTER_HANDLED ; 
 int FILTER_STRAY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  oce_arm_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
oce_fast_isr(void *arg)
{
	POCE_INTR_INFO ii = (POCE_INTR_INFO) arg;
	POCE_SOFTC sc = ii->sc;

	if (ii->eq == NULL)
		return FILTER_STRAY;

	oce_arm_eq(sc, ii->eq->eq_id, 0, FALSE, TRUE);

	taskqueue_enqueue(ii->tq, &ii->task);

 	ii->eq->intr++;	

	return FILTER_HANDLED;
}