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
typedef  void* uint8_t ;
struct pmu_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pmu_ack_off (struct pmu_softc*) ; 
 int /*<<< orphan*/  pmu_ack_on (struct pmu_softc*) ; 
 int /*<<< orphan*/  pmu_in (struct pmu_softc*) ; 
 scalar_t__ pmu_intr_state (struct pmu_softc*) ; 
 void* pmu_read_reg (struct pmu_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vSR ; 

__attribute__((used)) static inline int
pmu_read_byte(struct pmu_softc *sc, uint8_t *data)
{
	volatile uint8_t scratch;
	pmu_in(sc);
	scratch = pmu_read_reg(sc, vSR);
	pmu_ack_off(sc);
	/* wait for intr to come up */
	do {} while (pmu_intr_state(sc) == 0);
	pmu_ack_on(sc);
	do {} while (pmu_intr_state(sc));
	*data = pmu_read_reg(sc, vSR);
	return 0;
}