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
typedef  int uint8_t ;
struct otus_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_MAC_REG_MAC_ADDR_H ; 
 int /*<<< orphan*/  AR_MAC_REG_MAC_ADDR_L ; 
 int /*<<< orphan*/  OTUS_LOCK_ASSERT (struct otus_softc*) ; 
 int /*<<< orphan*/  otus_write (struct otus_softc*,int /*<<< orphan*/ ,int const) ; 
 int otus_write_barrier (struct otus_softc*) ; 

int
otus_set_macaddr(struct otus_softc *sc, const uint8_t *addr)
{
	OTUS_LOCK_ASSERT(sc);

	otus_write(sc, AR_MAC_REG_MAC_ADDR_L,
	    addr[0] | addr[1] << 8 | addr[2] << 16 | addr[3] << 24);
	otus_write(sc, AR_MAC_REG_MAC_ADDR_H,
	    addr[4] | addr[5] << 8);
	return otus_write_barrier(sc);
}