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
struct age_softc {int /*<<< orphan*/  age_int_task; int /*<<< orphan*/  age_tq; } ;

/* Variables and functions */
 int AGE_INTRS ; 
 int /*<<< orphan*/  AGE_INTR_STATUS ; 
 int CSR_READ_4 (struct age_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct age_softc*,int /*<<< orphan*/ ,int) ; 
 int FILTER_HANDLED ; 
 int FILTER_STRAY ; 
 int INTR_DIS_INT ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
age_intr(void *arg)
{
	struct age_softc *sc;
	uint32_t status;

	sc = (struct age_softc *)arg;

	status = CSR_READ_4(sc, AGE_INTR_STATUS);
	if (status == 0 || (status & AGE_INTRS) == 0)
		return (FILTER_STRAY);
	/* Disable interrupts. */
	CSR_WRITE_4(sc, AGE_INTR_STATUS, status | INTR_DIS_INT);
	taskqueue_enqueue(sc->age_tq, &sc->age_int_task);

	return (FILTER_HANDLED);
}