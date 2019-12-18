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
struct zyd_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static uint8_t
zyd_plcp_signal(struct zyd_softc *sc, int rate)
{
	switch (rate) {
	/* OFDM rates (cf IEEE Std 802.11a-1999, pp. 14 Table 80) */
	case 12:
		return (0xb);
	case 18:
		return (0xf);
	case 24:
		return (0xa);
	case 36:
		return (0xe);
	case 48:
		return (0x9);
	case 72:
		return (0xd);
	case 96:
		return (0x8);
	case 108:
		return (0xc);
	/* CCK rates (NB: not IEEE std, device-specific) */
	case 2:
		return (0x0);
	case 4:
		return (0x1);
	case 11:
		return (0x2);
	case 22:
		return (0x3);
	}

	device_printf(sc->sc_dev, "unsupported rate %d\n", rate);
	return (0x0);
}