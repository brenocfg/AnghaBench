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
struct sbus_softc {uintptr_t sc_ign; } ;
struct sbus_devinfo {uintptr_t sdi_burstsz; uintptr_t sdi_clockfreq; uintptr_t sdi_slot; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
#define  SBUS_IVAR_BURSTSZ 131 
#define  SBUS_IVAR_CLOCKFREQ 130 
#define  SBUS_IVAR_IGN 129 
#define  SBUS_IVAR_SLOT 128 
 struct sbus_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct sbus_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sbus_read_ivar(device_t dev, device_t child, int which, uintptr_t *result)
{
	struct sbus_softc *sc;
	struct sbus_devinfo *dinfo;

	sc = device_get_softc(dev);
	if ((dinfo = device_get_ivars(child)) == NULL)
		return (ENOENT);
	switch (which) {
	case SBUS_IVAR_BURSTSZ:
		*result = dinfo->sdi_burstsz;
		break;
	case SBUS_IVAR_CLOCKFREQ:
		*result = dinfo->sdi_clockfreq;
		break;
	case SBUS_IVAR_IGN:
		*result = sc->sc_ign;
		break;
	case SBUS_IVAR_SLOT:
		*result = dinfo->sdi_slot;
		break;
	default:
		return (ENOENT);
	}
	return (0);
}