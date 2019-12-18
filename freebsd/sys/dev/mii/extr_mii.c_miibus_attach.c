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
struct miibus_ivars {int /*<<< orphan*/  ifp; int /*<<< orphan*/  ifmedia_sts; int /*<<< orphan*/  ifmedia_upd; } ;
struct mii_data {int /*<<< orphan*/  mii_phys; int /*<<< orphan*/  mii_ifp; int /*<<< orphan*/  mii_media; } ;
struct mii_attach_args {struct mii_data* mii_data; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IFCAP_LINKSTATE ; 
 int /*<<< orphan*/  IFM_IMASK ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 void* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setcapabilitiesbit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setcapenablebit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
miibus_attach(device_t dev)
{
	struct miibus_ivars	*ivars;
	struct mii_attach_args	*ma;
	struct mii_data		*mii;
	device_t		*children;
	int			i, nchildren;

	mii = device_get_softc(dev);
	if (device_get_children(dev, &children, &nchildren) == 0) {
		for (i = 0; i < nchildren; i++) {
			ma = device_get_ivars(children[i]);
			ma->mii_data = mii;
		}
		free(children, M_TEMP);
	}
	if (nchildren == 0) {
		device_printf(dev, "cannot get children\n");
		return (ENXIO);
	}
	ivars = device_get_ivars(dev);
	ifmedia_init(&mii->mii_media, IFM_IMASK, ivars->ifmedia_upd,
	    ivars->ifmedia_sts);
	mii->mii_ifp = ivars->ifp;
	if_setcapabilitiesbit(mii->mii_ifp, IFCAP_LINKSTATE, 0);
	if_setcapenablebit(mii->mii_ifp, IFCAP_LINKSTATE, 0);
	LIST_INIT(&mii->mii_phys);

	return (bus_generic_attach(dev));
}