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
struct alc_softc {int /*<<< orphan*/  alc_int_task; int /*<<< orphan*/  alc_tq; } ;

/* Variables and functions */
 int ALC_INTRS ; 
 int /*<<< orphan*/  ALC_INTR_STATUS ; 
 int CSR_READ_4 (struct alc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct alc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FILTER_HANDLED ; 
 int FILTER_STRAY ; 
 int /*<<< orphan*/  INTR_DIS_INT ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
alc_intr(void *arg)
{
	struct alc_softc *sc;
	uint32_t status;

	sc = (struct alc_softc *)arg;

	status = CSR_READ_4(sc, ALC_INTR_STATUS);
	if ((status & ALC_INTRS) == 0)
		return (FILTER_STRAY);
	/* Disable interrupts. */
	CSR_WRITE_4(sc, ALC_INTR_STATUS, INTR_DIS_INT);
	taskqueue_enqueue(sc->alc_tq, &sc->alc_int_task);

	return (FILTER_HANDLED);
}