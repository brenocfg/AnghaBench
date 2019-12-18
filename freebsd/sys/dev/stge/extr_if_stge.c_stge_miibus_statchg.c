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
struct stge_softc {int /*<<< orphan*/  sc_link_task; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct stge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_swi ; 

__attribute__((used)) static void
stge_miibus_statchg(device_t dev)
{
	struct stge_softc *sc;

	sc = device_get_softc(dev);
	taskqueue_enqueue(taskqueue_swi, &sc->sc_link_task);
}