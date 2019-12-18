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
typedef  int /*<<< orphan*/  uint32_t ;
struct machfb_softc {int sc_flags; int sc_ymargin; int sc_xmargin; } ;

/* Variables and functions */
 int CRTC_DBL_SCAN_EN ; 
 int /*<<< orphan*/  CUR_HORZ_VERT_OFF ; 
 int /*<<< orphan*/  CUR_HORZ_VERT_POSN ; 
 int /*<<< orphan*/  GEN_TEST_CNTL ; 
 int MACHFB_CUREN ; 
 int /*<<< orphan*/  machfb_cursor_enable (struct machfb_softc*,int) ; 
 int machfb_cursor_install (struct machfb_softc*) ; 
 int regr (struct machfb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regw (struct machfb_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
machfb_putm(video_adapter_t *adp, int x, int y, uint8_t *pixel_image,
    uint32_t pixel_mask, int size, int width)
{
	struct machfb_softc *sc;
	int error;

	sc = (struct machfb_softc *)adp;

	if ((!(sc->sc_flags & MACHFB_CUREN)) &&
	    (error = machfb_cursor_install(sc)) < 0)
		return (error);
	else {
		/*
		 * The hardware cursor always must be disabled when
		 * fiddling with its bits otherwise some artifacts
		 * may appear on the screen.
		 */
		machfb_cursor_enable(sc, 0);
	}

	regw(sc, CUR_HORZ_VERT_OFF, 0);
	if ((regr(sc, GEN_TEST_CNTL) & CRTC_DBL_SCAN_EN) != 0)
		y <<= 1;
	regw(sc, CUR_HORZ_VERT_POSN, ((y + sc->sc_ymargin) << 16) |
	    (x + sc->sc_xmargin));
	machfb_cursor_enable(sc, 1);
	sc->sc_flags |= MACHFB_CUREN;

	return (0);
}