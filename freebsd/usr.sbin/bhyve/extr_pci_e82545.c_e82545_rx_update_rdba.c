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
typedef  int uint64_t ;
struct e82545_softc {int esc_rdba; int esc_RDBAL; int /*<<< orphan*/  esc_RDLEN; int /*<<< orphan*/  esc_ctx; int /*<<< orphan*/  esc_rxdesc; scalar_t__ esc_RDBAH; } ;

/* Variables and functions */
 int /*<<< orphan*/  paddr_guest2host (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
e82545_rx_update_rdba(struct e82545_softc *sc)
{

	/* XXX verify desc base/len within phys mem range */
	sc->esc_rdba = (uint64_t)sc->esc_RDBAH << 32 |
	    sc->esc_RDBAL;
	
	/* Cache host mapping of guest descriptor array */
	sc->esc_rxdesc = paddr_guest2host(sc->esc_ctx,
	    sc->esc_rdba, sc->esc_RDLEN);	
}