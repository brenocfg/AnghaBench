#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int /*<<< orphan*/  link_task; } ;
typedef  TYPE_1__ ae_softc_t ;

/* Variables and functions */
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_swi ; 

__attribute__((used)) static void
ae_miibus_statchg(device_t dev)
{
	ae_softc_t *sc;

	sc = device_get_softc(dev);
	taskqueue_enqueue(taskqueue_swi, &sc->link_task);
}