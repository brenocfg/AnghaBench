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
struct mge_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MGE_INT_CAUSE ; 
 int /*<<< orphan*/  MGE_INT_MASK ; 
 int /*<<< orphan*/  MGE_PORT_INT_CAUSE ; 
 int /*<<< orphan*/  MGE_PORT_INT_CAUSE_EXT ; 
 int MGE_PORT_INT_EXTEND ; 
 int MGE_PORT_INT_EXT_RXOR ; 
 int MGE_PORT_INT_EXT_TXBUF0 ; 
 int MGE_PORT_INT_EXT_TXERR0 ; 
 int MGE_PORT_INT_EXT_TXUR ; 
 int /*<<< orphan*/  MGE_PORT_INT_MASK ; 
 int /*<<< orphan*/  MGE_PORT_INT_MASK_EXT ; 
 int MGE_PORT_INT_RXERRQ0 ; 
 int MGE_PORT_INT_RXQ0 ; 
 int /*<<< orphan*/  MGE_WRITE (struct mge_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mge_intrs_ctrl(struct mge_softc *sc, int enable)
{

	if (enable) {
		MGE_WRITE(sc, MGE_PORT_INT_MASK , MGE_PORT_INT_RXQ0 |
		    MGE_PORT_INT_EXTEND | MGE_PORT_INT_RXERRQ0);
		MGE_WRITE(sc, MGE_PORT_INT_MASK_EXT , MGE_PORT_INT_EXT_TXERR0 |
		    MGE_PORT_INT_EXT_RXOR | MGE_PORT_INT_EXT_TXUR |
		    MGE_PORT_INT_EXT_TXBUF0);
	} else {
		MGE_WRITE(sc, MGE_INT_CAUSE, 0x0);
		MGE_WRITE(sc, MGE_INT_MASK, 0x0);

		MGE_WRITE(sc, MGE_PORT_INT_CAUSE, 0x0);
		MGE_WRITE(sc, MGE_PORT_INT_CAUSE_EXT, 0x0);

		MGE_WRITE(sc, MGE_PORT_INT_MASK, 0x0);
		MGE_WRITE(sc, MGE_PORT_INT_MASK_EXT, 0x0);
	}
}