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
struct adapter {int /*<<< orphan*/  flags; int /*<<< orphan*/ ** tq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAPTER_LOCK_ASSERT_NOTOWNED (struct adapter*) ; 
 int /*<<< orphan*/  FULL_INIT_DONE ; 
 int nitems (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  t4_teardown_adapter_queues (struct adapter*) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 

int
adapter_full_uninit(struct adapter *sc)
{
	int i;

	ADAPTER_LOCK_ASSERT_NOTOWNED(sc);

	t4_teardown_adapter_queues(sc);

	for (i = 0; i < nitems(sc->tq) && sc->tq[i]; i++) {
		taskqueue_free(sc->tq[i]);
		sc->tq[i] = NULL;
	}

	sc->flags &= ~FULL_INIT_DONE;

	return (0);
}