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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct tda19988_softc {int /*<<< orphan*/  sc_edid_len; int /*<<< orphan*/ * sc_edid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 struct tda19988_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tda19988_get_edid(device_t dev, uint8_t **edid, uint32_t *edid_len)
{
	struct tda19988_softc *sc;

	sc = device_get_softc(dev);

	if (sc->sc_edid) {
		*edid = sc->sc_edid;
		*edid_len = sc->sc_edid_len;
	} else
		return (ENXIO);

	return (0);
}