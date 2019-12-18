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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u_int ;
struct cfi_softc {int sc_width; int /*<<< orphan*/  sc_handle; int /*<<< orphan*/  sc_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_space_read_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 

uint32_t
cfi_read(struct cfi_softc *sc, u_int ofs)
{
	uint32_t val;
	uint16_t sval;

	ofs &= ~(sc->sc_width - 1);
	switch (sc->sc_width) {
	case 1:
		val = bus_space_read_1(sc->sc_tag, sc->sc_handle, ofs);
		break;
	case 2:
		sval = bus_space_read_2(sc->sc_tag, sc->sc_handle, ofs);
#ifdef CFI_HARDWAREBYTESWAP
		val = sval;
#else
		val = le16toh(sval);
#endif
		break;
	case 4:
		val = bus_space_read_4(sc->sc_tag, sc->sc_handle, ofs);
#ifndef CFI_HARDWAREBYTESWAP
		val = le32toh(val);
#endif
		break;
	default:
		val = ~0;
		break;
	}
	return (val);
}