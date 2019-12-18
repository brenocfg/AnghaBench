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
struct hwpstate_softc {int cfnum; struct hwpstate_setting* hwpstate_settings; } ;
struct hwpstate_setting {int /*<<< orphan*/  lat; int /*<<< orphan*/  power; int /*<<< orphan*/  volts; int /*<<< orphan*/  freq; } ;
struct cf_setting {int /*<<< orphan*/  dev; int /*<<< orphan*/  lat; int /*<<< orphan*/  power; int /*<<< orphan*/  volts; int /*<<< orphan*/  freq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
 struct hwpstate_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hwpstate_settings(device_t dev, struct cf_setting *sets, int *count)
{
	struct hwpstate_softc *sc;
	struct hwpstate_setting set;
	int i;

	if (sets == NULL || count == NULL)
		return (EINVAL);
	sc = device_get_softc(dev);
	if (*count < sc->cfnum)
		return (E2BIG);
	for (i = 0; i < sc->cfnum; i++, sets++) {
		set = sc->hwpstate_settings[i];
		sets->freq = set.freq;
		sets->volts = set.volts;
		sets->power = set.power;
		sets->lat = set.lat;
		sets->dev = dev;
	}
	*count = sc->cfnum;

	return (0);
}