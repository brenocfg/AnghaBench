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
struct machfb_softc {scalar_t__ sc_height; scalar_t__ sc_xmargin; scalar_t__ sc_width; scalar_t__ sc_ymargin; } ;

/* Variables and functions */
 int /*<<< orphan*/  machfb_fill_rect (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
machfb_set_border(video_adapter_t *adp, int border)
{
	struct machfb_softc *sc;

	sc = (struct machfb_softc *)adp;

	machfb_fill_rect(adp, border, 0, 0, sc->sc_width, sc->sc_ymargin);
	machfb_fill_rect(adp, border, 0, sc->sc_height - sc->sc_ymargin,
	    sc->sc_width, sc->sc_ymargin);
	machfb_fill_rect(adp, border, 0, 0, sc->sc_xmargin, sc->sc_height);
	machfb_fill_rect(adp, border, sc->sc_width - sc->sc_xmargin, 0,
	    sc->sc_xmargin, sc->sc_height);

	return (0);
}