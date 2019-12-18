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
struct cf_setting {scalar_t__ freq; } ;
struct TYPE_2__ {scalar_t__ freq; int /*<<< orphan*/  id16; } ;
typedef  TYPE_1__ freq_info ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 struct est_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  est_set_id16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
est_set(device_t dev, const struct cf_setting *set)
{
	struct est_softc *sc;
	freq_info *f;

	/* Find the setting matching the requested one. */
	sc = device_get_softc(dev);
	for (f = sc->freq_list; f < sc->freq_list + sc->flist_len; f++) {
		if (f->freq == set->freq)
			break;
	}
	if (f->freq == 0)
		return (EINVAL);

	/* Read the current register, mask out the old, set the new id. */
	est_set_id16(dev, f->id16, 0);

	return (0);
}