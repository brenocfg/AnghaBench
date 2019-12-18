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
struct pn_softc {int errata; int powernow_max_states; int pn_type; TYPE_1__* powernow_states; } ;
struct cf_setting {int /*<<< orphan*/  freq; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int freq; int fid; int vid; } ;

/* Variables and functions */
 scalar_t__ CPUFREQ_CMP (int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENXIO ; 
 int PENDING_STUCK ; 
#define  PN7_TYPE 129 
#define  PN8_TYPE 128 
 struct pn_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pn7_setfidvid (struct pn_softc*,int,int) ; 
 int pn8_setfidvid (struct pn_softc*,int,int) ; 

__attribute__((used)) static int
pn_set(device_t dev, const struct cf_setting *cf)
{
	struct pn_softc *sc;
	int fid, vid;
	int i;
	int rv;

	if (cf == NULL)
		return (EINVAL);
	sc = device_get_softc(dev);

	if (sc->errata & PENDING_STUCK)
		return (ENXIO);

	for (i = 0; i < sc->powernow_max_states; ++i)
		if (CPUFREQ_CMP(sc->powernow_states[i].freq / 1000, cf->freq))
			break;

	fid = sc->powernow_states[i].fid;
	vid = sc->powernow_states[i].vid;

	rv = ENODEV;

	switch (sc->pn_type) {
	case PN7_TYPE:
		rv = pn7_setfidvid(sc, fid, vid);
		break;
	case PN8_TYPE:
		rv = pn8_setfidvid(sc, fid, vid);
		break;
	}

	return (rv);
}