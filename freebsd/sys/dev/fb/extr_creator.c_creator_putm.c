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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct creator_softc {int sc_flags; int sc_ymargin; int sc_xmargin; } ;

/* Variables and functions */
 int CREATOR_CUREN ; 
 int /*<<< orphan*/  FFB_DAC ; 
 int FFB_DAC_CUR_POS ; 
 int /*<<< orphan*/  FFB_DAC_TYPE2 ; 
 int /*<<< orphan*/  FFB_DAC_VALUE2 ; 
 int /*<<< orphan*/  FFB_WRITE (struct creator_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  creator_cursor_enable (struct creator_softc*,int) ; 
 int /*<<< orphan*/  creator_cursor_install (struct creator_softc*) ; 

__attribute__((used)) static int
creator_putm(video_adapter_t *adp, int x, int y, u_int8_t *pixel_image,
    u_int32_t pixel_mask, int size, int width)
{
	struct creator_softc *sc;

	sc = (struct creator_softc *)adp;
	if (!(sc->sc_flags & CREATOR_CUREN)) {
		creator_cursor_install(sc);
		creator_cursor_enable(sc, 1);
		sc->sc_flags |= CREATOR_CUREN;
	}
	FFB_WRITE(sc, FFB_DAC, FFB_DAC_TYPE2, FFB_DAC_CUR_POS);
	FFB_WRITE(sc, FFB_DAC, FFB_DAC_VALUE2,
	    ((y + sc->sc_ymargin) << 16) | (x + sc->sc_xmargin));
	return (0);
}