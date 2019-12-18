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
struct est_softc {int flist_len; TYPE_1__* freq_list; } ;
struct cf_setting {int /*<<< orphan*/  dev; int /*<<< orphan*/  lat; int /*<<< orphan*/  power; int /*<<< orphan*/  volts; int /*<<< orphan*/  freq; } ;
struct TYPE_2__ {int /*<<< orphan*/  power; int /*<<< orphan*/  volts; int /*<<< orphan*/  freq; } ;
typedef  TYPE_1__ freq_info ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int E2BIG ; 
 int EST_MAX_SETTINGS ; 
 int /*<<< orphan*/  EST_TRANS_LAT ; 
 struct est_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
est_settings(device_t dev, struct cf_setting *sets, int *count)
{
	struct est_softc *sc;
	freq_info *f;
	int i;

	sc = device_get_softc(dev);
	if (*count < EST_MAX_SETTINGS)
		return (E2BIG);

	i = 0;
	for (f = sc->freq_list; f < sc->freq_list + sc->flist_len; f++, i++) {
		sets[i].freq = f->freq;
		sets[i].volts = f->volts;
		sets[i].power = f->power;
		sets[i].lat = EST_TRANS_LAT;
		sets[i].dev = dev;
	}
	*count = i;

	return (0);
}