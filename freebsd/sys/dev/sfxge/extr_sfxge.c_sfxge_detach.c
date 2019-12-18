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
struct sfxge_softc {int /*<<< orphan*/  ifnet; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct sfxge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_destroy (struct sfxge_softc*) ; 
 int /*<<< orphan*/  sfxge_ifnet_fini (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_vpd_fini (struct sfxge_softc*) ; 

__attribute__((used)) static int
sfxge_detach(device_t dev)
{
	struct sfxge_softc *sc;

	sc = device_get_softc(dev);

	sfxge_vpd_fini(sc);

	/* Destroy the ifnet. */
	sfxge_ifnet_fini(sc->ifnet);

	/* Tear down hardware. */
	sfxge_destroy(sc);

	return (0);
}