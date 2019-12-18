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
typedef  int /*<<< orphan*/  video_adapter_t ;
struct machfb_softc {int sc_bg_cache; int sc_fg_cache; scalar_t__ sc_draw_cache; } ;

/* Variables and functions */

__attribute__((used)) static int
machfb_set_mode(video_adapter_t *adp, int mode)
{
	struct machfb_softc *sc;

	sc = (struct machfb_softc *)adp;

	sc->sc_bg_cache = -1;
	sc->sc_fg_cache = -1;
	sc->sc_draw_cache = 0;

	return (0);
}