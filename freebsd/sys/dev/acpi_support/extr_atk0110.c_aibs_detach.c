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
struct aibs_softc {int /*<<< orphan*/ * sc_asens_all; int /*<<< orphan*/ * sc_asens_fan; int /*<<< orphan*/ * sc_asens_temp; int /*<<< orphan*/ * sc_asens_volt; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 struct aibs_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aibs_detach(device_t dev)
{
	struct aibs_softc	*sc = device_get_softc(dev);

	if (sc->sc_asens_volt != NULL)
		free(sc->sc_asens_volt, M_DEVBUF);
	if (sc->sc_asens_temp != NULL)
		free(sc->sc_asens_temp, M_DEVBUF);
	if (sc->sc_asens_fan != NULL)
		free(sc->sc_asens_fan, M_DEVBUF);
	if (sc->sc_asens_all != NULL)
		free(sc->sc_asens_all, M_DEVBUF);
	return (0);
}