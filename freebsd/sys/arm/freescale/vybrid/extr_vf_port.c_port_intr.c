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
struct port_softc {int dummy; } ;
struct port_event {int enabled; int /*<<< orphan*/  ih_user; int /*<<< orphan*/  (* ih ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int NGPIO ; 
 int PCR_ISF ; 
 int /*<<< orphan*/  PORT_PCR (int) ; 
 int READ4 (struct port_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct port_softc*,int /*<<< orphan*/ ,int) ; 
 struct port_event* event_map ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
port_intr(void *arg)
{
	struct port_event *pev;
	struct port_softc *sc;
	int reg;
	int i;

	sc = arg;

	for (i = 0; i < NGPIO; i++) {
		reg = READ4(sc, PORT_PCR(i));
		if (reg & PCR_ISF) {

			/* Clear interrupt */
			WRITE4(sc, PORT_PCR(i), reg);

			/* Handle event */
			pev = &event_map[i];
			if (pev->enabled == 1) {
				if (pev->ih != NULL) {
					pev->ih(pev->ih_user);
				}
			}
		}
	}

	return (FILTER_HANDLED);
}