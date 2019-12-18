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
struct cas_softc {int /*<<< orphan*/  sc_intr_task; int /*<<< orphan*/  sc_tq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAS_INTMASK ; 
 int CAS_INTR_SUMMARY ; 
 int CAS_READ_4 (struct cas_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAS_STATUS_ALIAS ; 
 int /*<<< orphan*/  CAS_WRITE_4 (struct cas_softc*,int /*<<< orphan*/ ,int) ; 
 int FILTER_HANDLED ; 
 int FILTER_STRAY ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cas_intr(void *v)
{
	struct cas_softc *sc = v;

	if (__predict_false((CAS_READ_4(sc, CAS_STATUS_ALIAS) &
	    CAS_INTR_SUMMARY) == 0))
		return (FILTER_STRAY);

	/* Disable interrupts. */
	CAS_WRITE_4(sc, CAS_INTMASK, 0xffffffff);
	taskqueue_enqueue(sc->sc_tq, &sc->sc_intr_task);

	return (FILTER_HANDLED);
}