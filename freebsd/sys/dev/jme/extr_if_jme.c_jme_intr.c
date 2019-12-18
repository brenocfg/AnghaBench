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
struct jme_softc {int /*<<< orphan*/  jme_int_task; int /*<<< orphan*/  jme_tq; } ;

/* Variables and functions */
 int CSR_READ_4 (struct jme_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct jme_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FILTER_HANDLED ; 
 int FILTER_STRAY ; 
 int /*<<< orphan*/  JME_INTRS ; 
 int /*<<< orphan*/  JME_INTR_MASK_CLR ; 
 int /*<<< orphan*/  JME_INTR_REQ_STATUS ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
jme_intr(void *arg)
{
	struct jme_softc *sc;
	uint32_t status;

	sc = (struct jme_softc *)arg;

	status = CSR_READ_4(sc, JME_INTR_REQ_STATUS);
	if (status == 0 || status == 0xFFFFFFFF)
		return (FILTER_STRAY);
	/* Disable interrupts. */
	CSR_WRITE_4(sc, JME_INTR_MASK_CLR, JME_INTRS);
	taskqueue_enqueue(sc->jme_tq, &sc->jme_int_task);

	return (FILTER_HANDLED);
}