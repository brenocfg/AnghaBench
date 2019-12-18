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
typedef  int u_long ;
struct fbtype {int /*<<< orphan*/  fb_size; int /*<<< orphan*/  fb_cmsize; int /*<<< orphan*/  fb_depth; int /*<<< orphan*/  fb_width; int /*<<< orphan*/  fb_height; int /*<<< orphan*/  fb_type; } ;
struct fbcursor {int set; int /*<<< orphan*/  enable; } ;
struct creator_softc {int /*<<< orphan*/  sc_flags; int /*<<< orphan*/  sc_width; int /*<<< orphan*/  sc_height; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CREATOR_CUREN ; 
 int ENODEV ; 
#define  FBIOGTYPE 129 
#define  FBIOSCURSOR 128 
 int /*<<< orphan*/  FBTYPE_CREATOR ; 
 int FB_CUR_SETCUR ; 
 int /*<<< orphan*/  creator_cursor_enable (struct creator_softc*,int /*<<< orphan*/ ) ; 
 int fb_commonioctl (int /*<<< orphan*/ *,int,scalar_t__) ; 

__attribute__((used)) static int
creator_ioctl(video_adapter_t *adp, u_long cmd, caddr_t data)
{
	struct creator_softc *sc;
	struct fbcursor *fbc;
	struct fbtype *fb;

	sc = (struct creator_softc *)adp;
	switch (cmd) {
	case FBIOGTYPE:
		fb = (struct fbtype *)data;
		fb->fb_type = FBTYPE_CREATOR;
		fb->fb_height = sc->sc_height;
		fb->fb_width = sc->sc_width;
		fb->fb_depth = fb->fb_cmsize = fb->fb_size = 0;
		break;
	case FBIOSCURSOR:
		fbc = (struct fbcursor *)data;
		if (fbc->set & FB_CUR_SETCUR && fbc->enable == 0) {
			creator_cursor_enable(sc, 0);
			sc->sc_flags &= ~CREATOR_CUREN;
		} else
			return (ENODEV);
		break;
		break;
	default:
		return (fb_commonioctl(adp, cmd, data));
	}
	return (0);
}