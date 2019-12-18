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
typedef  int u_int32_t ;
struct hme_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int BUS_SPACE_BARRIER_READ ; 
 int BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  HME_MAC_BARRIER (struct hme_softc*,int,int,int) ; 
 int HME_MAC_READ_4 (struct hme_softc*,int) ; 
 int /*<<< orphan*/  HME_MAC_WRITE_4 (struct hme_softc*,int,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
hme_mac_bitflip(struct hme_softc *sc, u_int32_t reg, u_int32_t val,
    u_int32_t clr, u_int32_t set)
{
	int i = 0;

	val &= ~clr;
	val |= set;
	HME_MAC_WRITE_4(sc, reg, val);
	HME_MAC_BARRIER(sc, reg, 4,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
	if (clr == 0 && set == 0)
		return (1);	/* just write, no bits to wait for */
	do {
		DELAY(100);
		i++;
		val = HME_MAC_READ_4(sc, reg);
		if (i > 40) {
			/* After 3.5ms, we should have been done. */
			device_printf(sc->sc_dev, "timeout while writing to "
			    "MAC configuration register\n");
			return (0);
		}
	} while ((val & clr) != 0 && (val & set) != set);
	return (1);
}