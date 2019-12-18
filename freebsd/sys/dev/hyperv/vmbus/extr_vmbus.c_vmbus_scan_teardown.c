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
struct vmbus_softc {int /*<<< orphan*/ * vmbus_subchtq; int /*<<< orphan*/ * vmbus_devtq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIANT_REQUIRED ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vmbus_scan_teardown(struct vmbus_softc *sc)
{

	GIANT_REQUIRED;
	if (sc->vmbus_devtq != NULL) {
		mtx_unlock(&Giant);
		taskqueue_free(sc->vmbus_devtq);
		mtx_lock(&Giant);
		sc->vmbus_devtq = NULL;
	}
	if (sc->vmbus_subchtq != NULL) {
		mtx_unlock(&Giant);
		taskqueue_free(sc->vmbus_subchtq);
		mtx_lock(&Giant);
		sc->vmbus_subchtq = NULL;
	}
}