#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct mii_data {int /*<<< orphan*/  mii_media; int /*<<< orphan*/  mii_ifp; } ;
struct TYPE_15__ {scalar_t__ es_port; int es_flags; int /*<<< orphan*/  es_ifr; int /*<<< orphan*/  es_pvid; } ;
typedef  TYPE_1__ etherswitch_port_t ;
struct TYPE_16__ {scalar_t__ num_ports; } ;
typedef  TYPE_2__ e6000sw_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  E6000SW_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  E6000SW_LOCK_ASSERT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E6000SW_UNLOCK (TYPE_2__*) ; 
 int EINVAL ; 
 int ETHERSWITCH_PORT_DROPTAGGED ; 
 int ETHERSWITCH_PORT_DROPUNTAGGED ; 
 int /*<<< orphan*/  PORT_CONTROL2 ; 
 int /*<<< orphan*/  PORT_CONTROL2_DISC_TAGGED ; 
 int /*<<< orphan*/  PORT_CONTROL2_DISC_UNTAGGED ; 
 int /*<<< orphan*/  REG_PORT (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  SA_UNLOCKED ; 
 int /*<<< orphan*/  SIOCSIFMEDIA ; 
 TYPE_2__* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ e6000sw_is_phyport (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  e6000sw_is_portenabled (TYPE_2__*,scalar_t__) ; 
 struct mii_data* e6000sw_miiforphy (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  e6000sw_readreg (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e6000sw_set_pvid (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e6000sw_writereg (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ifmedia_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
e6000sw_setport(device_t dev, etherswitch_port_t *p)
{
	e6000sw_softc_t *sc;
	int err;
	struct mii_data *mii;
	uint32_t reg;

	sc = device_get_softc(dev);
	E6000SW_LOCK_ASSERT(sc, SA_UNLOCKED);

	if (p->es_port >= sc->num_ports || p->es_port < 0)
		return (EINVAL);
	if (!e6000sw_is_portenabled(sc, p->es_port))
		return (0);

	/* Port flags. */
	reg = e6000sw_readreg(sc, REG_PORT(sc, p->es_port), PORT_CONTROL2);
	if (p->es_flags & ETHERSWITCH_PORT_DROPTAGGED)
		reg |= PORT_CONTROL2_DISC_TAGGED;
	else
		reg &= ~PORT_CONTROL2_DISC_TAGGED;
	if (p->es_flags & ETHERSWITCH_PORT_DROPUNTAGGED)
		reg |= PORT_CONTROL2_DISC_UNTAGGED;
	else
		reg &= ~PORT_CONTROL2_DISC_UNTAGGED;
	e6000sw_writereg(sc, REG_PORT(sc, p->es_port), PORT_CONTROL2, reg);

	err = 0;
	E6000SW_LOCK(sc);
	if (p->es_pvid != 0)
		e6000sw_set_pvid(sc, p->es_port, p->es_pvid);
	if (e6000sw_is_phyport(sc, p->es_port)) {
		mii = e6000sw_miiforphy(sc, p->es_port);
		err = ifmedia_ioctl(mii->mii_ifp, &p->es_ifr, &mii->mii_media,
		    SIOCSIFMEDIA);
	}
	E6000SW_UNLOCK(sc);

	return (err);
}