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
struct age_softc {int /*<<< orphan*/  age_link_task; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct age_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_swi ; 

__attribute__((used)) static void
age_miibus_statchg(device_t dev)
{
	struct age_softc *sc;

	sc = device_get_softc(dev);
	taskqueue_enqueue(taskqueue_swi, &sc->age_link_task);
}