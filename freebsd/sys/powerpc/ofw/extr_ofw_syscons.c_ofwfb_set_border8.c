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
typedef  int /*<<< orphan*/  uint8_t ;
struct ofwfb_softc {int sc_ymargin; int sc_width; int sc_stride; int sc_height; int sc_xmargin; scalar_t__ sc_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ofwfb_background (int) ; 

__attribute__((used)) static int
ofwfb_set_border8(video_adapter_t *adp, int border)
{
	struct ofwfb_softc *sc;
	int i, j;
	uint8_t *addr;
	uint8_t bground;

	sc = (struct ofwfb_softc *)adp;

	bground = ofwfb_background(border);

	/* Set top margin */
	addr = (uint8_t *) sc->sc_addr;
	for (i = 0; i < sc->sc_ymargin; i++) {
		for (j = 0; j < sc->sc_width; j++) {
			*(addr + j) = bground;
		}
		addr += sc->sc_stride;
	}

	/* bottom margin */
	addr = (uint8_t *) sc->sc_addr + (sc->sc_height - sc->sc_ymargin)*sc->sc_stride;
	for (i = 0; i < sc->sc_ymargin; i++) {
		for (j = 0; j < sc->sc_width; j++) {
			*(addr + j) = bground;
		}
		addr += sc->sc_stride;
	}

	/* remaining left and right borders */
	addr = (uint8_t *) sc->sc_addr + sc->sc_ymargin*sc->sc_stride;
	for (i = 0; i < sc->sc_height - 2*sc->sc_xmargin; i++) {
		for (j = 0; j < sc->sc_xmargin; j++) {
			*(addr + j) = bground;
			*(addr + j + sc->sc_width - sc->sc_xmargin) = bground;
		}
		addr += sc->sc_stride;
	}

	return (0);
}