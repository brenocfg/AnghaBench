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
struct hn_softc {int /*<<< orphan*/  hn_netchg_init; int /*<<< orphan*/ * hn_mgmt_taskq; } ;

/* Variables and functions */
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hn_change_network(struct hn_softc *sc)
{

	if (sc->hn_mgmt_taskq != NULL)
		taskqueue_enqueue(sc->hn_mgmt_taskq, &sc->hn_netchg_init);
}