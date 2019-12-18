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
typedef  int uint32_t ;
struct ale_softc {int /*<<< orphan*/  ale_int_task; int /*<<< orphan*/  ale_tq; } ;

/* Variables and functions */
 int ALE_INTRS ; 
 int /*<<< orphan*/  ALE_INTR_STATUS ; 
 int CSR_READ_4 (struct ale_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct ale_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FILTER_HANDLED ; 
 int FILTER_STRAY ; 
 int /*<<< orphan*/  INTR_DIS_INT ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ale_intr(void *arg)
{
	struct ale_softc *sc;
	uint32_t status;

	sc = (struct ale_softc *)arg;

	status = CSR_READ_4(sc, ALE_INTR_STATUS);
	if ((status & ALE_INTRS) == 0)
		return (FILTER_STRAY);
	/* Disable interrupts. */
	CSR_WRITE_4(sc, ALE_INTR_STATUS, INTR_DIS_INT);
	taskqueue_enqueue(sc->ale_tq, &sc->ale_int_task);

	return (FILTER_HANDLED);
}