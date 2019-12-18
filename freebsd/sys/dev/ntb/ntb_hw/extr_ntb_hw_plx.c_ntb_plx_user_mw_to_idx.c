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
struct ntb_plx_softc {int split; } ;

/* Variables and functions */

__attribute__((used)) static unsigned
ntb_plx_user_mw_to_idx(struct ntb_plx_softc *sc, unsigned uidx, unsigned *sp)
{
	unsigned t;

	t = 1 << sc->split;
	if (uidx < t) {
		*sp = uidx;
		return (0);
	}
	*sp = 0;
	return (uidx - (t - 1));
}