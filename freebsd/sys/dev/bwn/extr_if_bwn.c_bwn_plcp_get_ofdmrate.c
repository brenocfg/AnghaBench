#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct bwn_softc {int /*<<< orphan*/  sc_dev; } ;
struct TYPE_2__ {int* raw; } ;
struct bwn_plcp6 {TYPE_1__ o; } ;
struct bwn_mac {struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 int BWN_OFDM_RATE_12MB ; 
 int BWN_OFDM_RATE_18MB ; 
 int BWN_OFDM_RATE_24MB ; 
 int BWN_OFDM_RATE_36MB ; 
 int BWN_OFDM_RATE_48MB ; 
 int BWN_OFDM_RATE_54MB ; 
 int BWN_OFDM_RATE_6MB ; 
 int BWN_OFDM_RATE_9MB ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
bwn_plcp_get_ofdmrate(struct bwn_mac *mac, struct bwn_plcp6 *plcp, uint8_t a)
{
	struct bwn_softc *sc = mac->mac_sc;

	KASSERT(a == 0, ("not support APHY\n"));

	switch (plcp->o.raw[0] & 0xf) {
	case 0xb:
		return (BWN_OFDM_RATE_6MB);
	case 0xf:
		return (BWN_OFDM_RATE_9MB);
	case 0xa:
		return (BWN_OFDM_RATE_12MB);
	case 0xe:
		return (BWN_OFDM_RATE_18MB);
	case 0x9:
		return (BWN_OFDM_RATE_24MB);
	case 0xd:
		return (BWN_OFDM_RATE_36MB);
	case 0x8:
		return (BWN_OFDM_RATE_48MB);
	case 0xc:
		return (BWN_OFDM_RATE_54MB);
	}
	device_printf(sc->sc_dev, "incorrect OFDM rate %d\n",
	    plcp->o.raw[0] & 0xf);
	return (-1);
}