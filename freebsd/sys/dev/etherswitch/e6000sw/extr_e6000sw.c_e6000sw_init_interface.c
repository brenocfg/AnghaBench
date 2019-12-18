#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ ** ifname; TYPE_2__** ifp; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ e6000sw_softc_t ;
struct TYPE_7__ {int if_flags; TYPE_1__* if_softc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int IFF_BROADCAST ; 
 int IFF_DRV_RUNNING ; 
 int IFF_SIMPLEX ; 
 int IFF_UP ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  M_E6000SW ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 TYPE_2__* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (TYPE_2__*) ; 
 int /*<<< orphan*/  if_initname (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int
e6000sw_init_interface(e6000sw_softc_t *sc, int port)
{
	char name[IFNAMSIZ];

	snprintf(name, IFNAMSIZ, "%sport", device_get_nameunit(sc->dev));

	sc->ifp[port] = if_alloc(IFT_ETHER);
	if (sc->ifp[port] == NULL)
		return (ENOMEM);
	sc->ifp[port]->if_softc = sc;
	sc->ifp[port]->if_flags |= IFF_UP | IFF_BROADCAST |
	    IFF_DRV_RUNNING | IFF_SIMPLEX;
	sc->ifname[port] = malloc(strlen(name) + 1, M_E6000SW, M_NOWAIT);
	if (sc->ifname[port] == NULL) {
		if_free(sc->ifp[port]);
		return (ENOMEM);
	}
	memcpy(sc->ifname[port], name, strlen(name) + 1);
	if_initname(sc->ifp[port], sc->ifname[port], port);

	return (0);
}