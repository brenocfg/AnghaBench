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
typedef  int /*<<< orphan*/  uint32_t ;
struct tsec_softc {int /*<<< orphan*/  tsec_ifp; } ;
typedef  int /*<<< orphan*/  macbuf ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 scalar_t__ IF_LLADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  TSEC_GLOBAL_LOCK_ASSERT (struct tsec_softc*) ; 
 int /*<<< orphan*/  TSEC_REG_MACSTNADDR1 ; 
 int /*<<< orphan*/  TSEC_REG_MACSTNADDR2 ; 
 int /*<<< orphan*/  TSEC_WRITE (struct tsec_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tsec_set_mac_address(struct tsec_softc *sc)
{
	uint32_t macbuf[2] = { 0, 0 };
	char *macbufp, *curmac;
	int i;

	TSEC_GLOBAL_LOCK_ASSERT(sc);

	KASSERT((ETHER_ADDR_LEN <= sizeof(macbuf)),
	    ("tsec_set_mac_address: (%d <= %zd", ETHER_ADDR_LEN,
	    sizeof(macbuf)));

	macbufp = (char *)macbuf;
	curmac = (char *)IF_LLADDR(sc->tsec_ifp);

	/* Correct order of MAC address bytes */
	for (i = 1; i <= ETHER_ADDR_LEN; i++)
		macbufp[ETHER_ADDR_LEN-i] = curmac[i-1];

	/* Initialize MAC station address MACSTNADDR2 and MACSTNADDR1 */
	TSEC_WRITE(sc, TSEC_REG_MACSTNADDR2, macbuf[1]);
	TSEC_WRITE(sc, TSEC_REG_MACSTNADDR1, macbuf[0]);
}