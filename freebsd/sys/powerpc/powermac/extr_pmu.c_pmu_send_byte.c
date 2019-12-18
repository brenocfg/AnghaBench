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
typedef  int /*<<< orphan*/  uint8_t ;
struct pmu_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pmu_ack_off (struct pmu_softc*) ; 
 int /*<<< orphan*/  pmu_ack_on (struct pmu_softc*) ; 
 scalar_t__ pmu_intr_state (struct pmu_softc*) ; 
 int /*<<< orphan*/  pmu_out (struct pmu_softc*) ; 
 int /*<<< orphan*/  pmu_write_reg (struct pmu_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vSR ; 

__attribute__((used)) static int
pmu_send_byte(struct pmu_softc *sc, uint8_t data)
{

	pmu_out(sc);
	pmu_write_reg(sc, vSR, data);
	pmu_ack_off(sc);
	/* wait for intr to come up */
	/* XXX should add a timeout and bail if it expires */
	do {} while (pmu_intr_state(sc) == 0);
	pmu_ack_on(sc);
	do {} while (pmu_intr_state(sc));
	pmu_ack_on(sc);
	return 0;
}