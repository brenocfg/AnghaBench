#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct est_softc {int /*<<< orphan*/  flist_len; int /*<<< orphan*/  freq_list; } ;
struct cf_setting {int /*<<< orphan*/  dev; int /*<<< orphan*/  lat; int /*<<< orphan*/  power; int /*<<< orphan*/  volts; int /*<<< orphan*/  freq; } ;
struct TYPE_3__ {int /*<<< orphan*/  power; int /*<<< orphan*/  volts; int /*<<< orphan*/  freq; } ;
typedef  TYPE_1__ freq_info ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  EST_TRANS_LAT ; 
 struct est_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 TYPE_1__* est_get_current (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
est_get(device_t dev, struct cf_setting *set)
{
	struct est_softc *sc;
	freq_info *f;

	sc = device_get_softc(dev);
	f = est_get_current(sc->freq_list, sc->flist_len);
	if (f == NULL)
		return (ENXIO);

	set->freq = f->freq;
	set->volts = f->volts;
	set->power = f->power;
	set->lat = EST_TRANS_LAT;
	set->dev = dev;
	return (0);
}