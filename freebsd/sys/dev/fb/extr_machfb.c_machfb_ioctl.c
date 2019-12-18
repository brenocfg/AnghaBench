#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  va_buffer_size; } ;
typedef  TYPE_1__ video_adapter_t ;
typedef  int u_long ;
struct machfb_softc {int sc_depth; int /*<<< orphan*/  sc_flags; int /*<<< orphan*/  sc_width; int /*<<< orphan*/  sc_height; } ;
struct fbtype {int fb_depth; int fb_cmsize; int /*<<< orphan*/  fb_size; int /*<<< orphan*/  fb_width; int /*<<< orphan*/  fb_height; int /*<<< orphan*/  fb_type; } ;
struct fbcursor {int set; int /*<<< orphan*/  enable; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int ENODEV ; 
#define  FBIOGTYPE 129 
#define  FBIOSCURSOR 128 
 int /*<<< orphan*/  FBTYPE_PCIMISC ; 
 int FB_CUR_SETCUR ; 
 int /*<<< orphan*/  MACHFB_CUREN ; 
 int fb_commonioctl (TYPE_1__*,int,scalar_t__) ; 
 int /*<<< orphan*/  machfb_cursor_enable (struct machfb_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
machfb_ioctl(video_adapter_t *adp, u_long cmd, caddr_t data)
{
	struct machfb_softc *sc;
	struct fbcursor *fbc;
	struct fbtype *fb;

	sc = (struct machfb_softc *)adp;

	switch (cmd) {
	case FBIOGTYPE:
		fb = (struct fbtype *)data;
		fb->fb_type = FBTYPE_PCIMISC;
		fb->fb_height = sc->sc_height;
		fb->fb_width = sc->sc_width;
		fb->fb_depth = sc->sc_depth;
		if (sc->sc_depth <= 1 || sc->sc_depth > 8)
			fb->fb_cmsize = 0;
		else
			fb->fb_cmsize = 1 << sc->sc_depth;
		fb->fb_size = adp->va_buffer_size;
		break;
	case FBIOSCURSOR:
		fbc = (struct fbcursor *)data;
		if (fbc->set & FB_CUR_SETCUR && fbc->enable == 0) {
			machfb_cursor_enable(sc, 0);
			sc->sc_flags &= ~MACHFB_CUREN;
		} else
			return (ENODEV);
		break;
	default:
		return (fb_commonioctl(adp, cmd, data));
	}

	return (0);
}