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
struct bge_softc {int /*<<< orphan*/  bge_intr_task; int /*<<< orphan*/  bge_tq; } ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bge_msi_intr(void *arg)
{
	struct bge_softc *sc;

	sc = (struct bge_softc *)arg;
	/*
	 * This interrupt is not shared and controller already
	 * disabled further interrupt.
	 */
	taskqueue_enqueue(sc->bge_tq, &sc->bge_intr_task);
	return (FILTER_HANDLED);
}