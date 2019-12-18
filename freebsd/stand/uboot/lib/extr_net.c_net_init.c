#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uboot_softc {unsigned long sc_txbufp; unsigned long sc_txbuf; int /*<<< orphan*/  sc_handle; } ;
struct netif {char* nif_unit; TYPE_2__* nif_driver; struct uboot_softc* nif_devdata; } ;
struct TYPE_6__ {scalar_t__ s_addr; } ;
struct iodesc {int /*<<< orphan*/  myea; TYPE_3__ myip; struct netif* io_netif; } ;
struct TYPE_4__ {int /*<<< orphan*/  hwaddr; } ;
struct device_info {TYPE_1__ di_net; } ;
struct TYPE_5__ {char* netif_bname; } ;

/* Variables and functions */
 unsigned long PKTALIGN ; 
 int /*<<< orphan*/  ether_sprintf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_env_net_params () ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ myip ; 
 int /*<<< orphan*/  panic (char*,char*,char*,...) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,int /*<<< orphan*/ ) ; 
 struct device_info* ub_dev_get (int /*<<< orphan*/ ) ; 
 int ub_dev_open (int /*<<< orphan*/ ) ; 
 struct uboot_softc uboot_softc ; 

__attribute__((used)) static void
net_init(struct iodesc *desc, void *machdep_hint)
{
	struct netif *nif = desc->io_netif;
	struct uboot_softc *sc;
	struct device_info *di;
	int err;

	sc = nif->nif_devdata = &uboot_softc;

	if ((err = ub_dev_open(sc->sc_handle)) != 0)
		panic("%s%d: initialisation failed with error %d",
		    nif->nif_driver->netif_bname, nif->nif_unit, err);

	/* Get MAC address */
	di = ub_dev_get(sc->sc_handle);
	memcpy(desc->myea, di->di_net.hwaddr, 6);
	if (memcmp (desc->myea, "\0\0\0\0\0\0", 6) == 0) {
		panic("%s%d: empty ethernet address!",
		    nif->nif_driver->netif_bname, nif->nif_unit);
	}

	/* Attempt to get netboot params from the u-boot env. */
	get_env_net_params();
	if (myip.s_addr != 0)
		desc->myip = myip;

#if defined(NETIF_DEBUG)
	printf("network: %s%d attached to %s\n", nif->nif_driver->netif_bname,
	    nif->nif_unit, ether_sprintf(desc->myea));
#endif

	/* Set correct alignment for TX packets */
	sc->sc_txbufp = sc->sc_txbuf;
	if ((unsigned long)sc->sc_txbufp % PKTALIGN)
		sc->sc_txbufp += PKTALIGN -
		    (unsigned long)sc->sc_txbufp % PKTALIGN;
}