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
typedef  int uint64_t ;
struct ifnet {struct glc_softc* if_softc; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifm_media; } ;
struct glc_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_bus; TYPE_1__ sc_media; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int GELIC_AUTO_NEG ; 
 int GELIC_FULL_DUPLEX ; 
 int /*<<< orphan*/  GELIC_SET_LINK_MODE ; 
 int GELIC_SPEED_10 ; 
 int GELIC_SPEED_100 ; 
 int GELIC_SPEED_1000 ; 
 int /*<<< orphan*/  GELIC_VLAN_TX_ETHERNET ; 
#define  IFM_1000_T 131 
#define  IFM_100_TX 130 
#define  IFM_10_T 129 
#define  IFM_AUTO 128 
 scalar_t__ IFM_ETHER ; 
 int IFM_FDX ; 
 int IFM_OPTIONS (int /*<<< orphan*/ ) ; 
 int IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ IFM_TYPE (int /*<<< orphan*/ ) ; 
 int lv1_net_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static int
glc_media_change(struct ifnet *ifp)
{
	struct glc_softc *sc = ifp->if_softc; 
	uint64_t mode, junk;
	int result;

	if (IFM_TYPE(sc->sc_media.ifm_media) != IFM_ETHER)
		return (EINVAL);

	switch (IFM_SUBTYPE(sc->sc_media.ifm_media)) {
	case IFM_AUTO:
		mode = GELIC_AUTO_NEG;
		break;
	case IFM_10_T:
		mode = GELIC_SPEED_10;
		break;
	case IFM_100_TX:
		mode = GELIC_SPEED_100;
		break;
	case IFM_1000_T:
		mode = GELIC_SPEED_1000 | GELIC_FULL_DUPLEX;
		break;
	default:
		return (EINVAL);
	}

	if (IFM_OPTIONS(sc->sc_media.ifm_media) & IFM_FDX)
		mode |= GELIC_FULL_DUPLEX;

	result = lv1_net_control(sc->sc_bus, sc->sc_dev, GELIC_SET_LINK_MODE,
	    GELIC_VLAN_TX_ETHERNET, mode, 0, &junk, &junk);

	return (result ? EIO : 0);
}