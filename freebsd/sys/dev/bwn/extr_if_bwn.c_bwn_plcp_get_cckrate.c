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
struct bwn_softc {int /*<<< orphan*/  sc_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * raw; } ;
struct bwn_plcp6 {TYPE_1__ o; } ;
struct bwn_mac {struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 int BWN_CCK_RATE_11MB ; 
 int BWN_CCK_RATE_1MB ; 
 int BWN_CCK_RATE_2MB ; 
 int BWN_CCK_RATE_5MB ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bwn_plcp_get_cckrate(struct bwn_mac *mac, struct bwn_plcp6 *plcp)
{
	struct bwn_softc *sc = mac->mac_sc;

	switch (plcp->o.raw[0]) {
	case 0x0a:
		return (BWN_CCK_RATE_1MB);
	case 0x14:
		return (BWN_CCK_RATE_2MB);
	case 0x37:
		return (BWN_CCK_RATE_5MB);
	case 0x6e:
		return (BWN_CCK_RATE_11MB);
	}
	device_printf(sc->sc_dev, "incorrect CCK rate %d\n", plcp->o.raw[0]);
	return (-1);
}