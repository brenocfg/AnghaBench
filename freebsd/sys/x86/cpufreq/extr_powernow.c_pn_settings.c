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
struct pn_softc {int powernow_max_states; TYPE_1__* powernow_states; int /*<<< orphan*/ * vid_to_volts; } ;
struct cf_setting {int freq; int lat; int /*<<< orphan*/  dev; int /*<<< orphan*/  volts; int /*<<< orphan*/  power; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int freq; size_t vid; int /*<<< orphan*/  power; } ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
 struct pn_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pn_settings(device_t dev, struct cf_setting *sets, int *count)
{
	struct pn_softc *sc;
	int i;

	if (sets == NULL|| count == NULL)
		return (EINVAL);
	sc = device_get_softc(dev);
	if (*count < sc->powernow_max_states)
		return (E2BIG);
	for (i = 0; i < sc->powernow_max_states; ++i) {
		sets[i].freq = sc->powernow_states[i].freq / 1000;
		sets[i].power = sc->powernow_states[i].power;
		sets[i].lat = 200;
		sets[i].volts = sc->vid_to_volts[sc->powernow_states[i].vid];
		sets[i].dev = dev;
	}
	*count = sc->powernow_max_states;

	return (0);
}