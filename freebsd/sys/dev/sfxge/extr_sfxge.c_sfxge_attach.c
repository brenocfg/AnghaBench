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
struct sfxge_softc {int /*<<< orphan*/  dev; struct ifnet* ifnet; int /*<<< orphan*/  enp; int /*<<< orphan*/  init_state; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPRINT (int /*<<< orphan*/ ,char*,...) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IFT_ETHER ; 
 int /*<<< orphan*/  SFXGE_REGISTERED ; 
 struct sfxge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  efx_nic_fini (int /*<<< orphan*/ ) ; 
 struct ifnet* if_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int sfxge_create (struct sfxge_softc*) ; 
 int /*<<< orphan*/  sfxge_destroy (struct sfxge_softc*) ; 
 int /*<<< orphan*/  sfxge_ifnet_fini (struct ifnet*) ; 
 int sfxge_ifnet_init (struct ifnet*,struct sfxge_softc*) ; 
 int sfxge_vpd_init (struct sfxge_softc*) ; 

__attribute__((used)) static int
sfxge_attach(device_t dev)
{
	struct sfxge_softc *sc;
	struct ifnet *ifp;
	int error;

	sc = device_get_softc(dev);
	sc->dev = dev;

	/* Allocate ifnet. */
	ifp = if_alloc(IFT_ETHER);
	if (ifp == NULL) {
		device_printf(dev, "Couldn't allocate ifnet\n");
		error = ENOMEM;
		goto fail;
	}
	sc->ifnet = ifp;

	/* Initialize hardware. */
	DBGPRINT(sc->dev, "create nic");
	if ((error = sfxge_create(sc)) != 0)
		goto fail2;

	/* Create the ifnet for the port. */
	DBGPRINT(sc->dev, "init ifnet");
	if ((error = sfxge_ifnet_init(ifp, sc)) != 0)
		goto fail3;

	DBGPRINT(sc->dev, "init vpd");
	if ((error = sfxge_vpd_init(sc)) != 0)
		goto fail4;

	/*
	 * NIC is initialized inside sfxge_create() and kept inialized
	 * to be able to initialize port to discover media types in
	 * sfxge_ifnet_init().
	 */
	efx_nic_fini(sc->enp);

	sc->init_state = SFXGE_REGISTERED;

	DBGPRINT(sc->dev, "success");
	return (0);

fail4:
	sfxge_ifnet_fini(ifp);
fail3:
	efx_nic_fini(sc->enp);
	sfxge_destroy(sc);

fail2:
	if_free(sc->ifnet);

fail:
	DBGPRINT(sc->dev, "failed %d", error);
	return (error);
}