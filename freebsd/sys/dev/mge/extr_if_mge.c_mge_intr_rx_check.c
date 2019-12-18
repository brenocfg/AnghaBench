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
struct mge_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MGE_PORT_INT_CAUSE ; 
 int /*<<< orphan*/  MGE_PORT_INT_CAUSE_EXT ; 
 int MGE_PORT_INT_EXT_RXOR ; 
 int MGE_PORT_INT_RXERRQ0 ; 
 int MGE_PORT_INT_RXQ0 ; 
 int /*<<< orphan*/  MGE_WRITE (struct mge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mge_intr_rx_locked (struct mge_softc*,int) ; 
 int /*<<< orphan*/  mge_reinit_rx (struct mge_softc*) ; 

__attribute__((used)) static void
mge_intr_rx_check(struct mge_softc *sc, uint32_t int_cause,
    uint32_t int_cause_ext)
{
	/* Check for resource error */
	if (int_cause & MGE_PORT_INT_RXERRQ0) {
		mge_reinit_rx(sc);
		MGE_WRITE(sc, MGE_PORT_INT_CAUSE,
		    ~(int_cause & MGE_PORT_INT_RXERRQ0));
	}

	int_cause &= MGE_PORT_INT_RXQ0;
	int_cause_ext &= MGE_PORT_INT_EXT_RXOR;

	if (int_cause || int_cause_ext) {
		MGE_WRITE(sc, MGE_PORT_INT_CAUSE, ~int_cause);
		MGE_WRITE(sc, MGE_PORT_INT_CAUSE_EXT, ~int_cause_ext);
		mge_intr_rx_locked(sc, -1);
	}
}