#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct TYPE_5__ {int vi_cheight; int vi_width; int vi_height; int vi_cwidth; } ;
typedef  TYPE_1__ video_info_t ;
struct TYPE_6__ {int va_flags; scalar_t__ va_window; TYPE_1__ va_info; } ;
typedef  TYPE_2__ video_adapter_t ;
struct ofwfb_softc {int sc_font_height; int sc_width; int sc_height; int sc_xmargin; int sc_ymargin; int /*<<< orphan*/  sc_va; int /*<<< orphan*/  sc_font; } ;

/* Variables and functions */
 int COL ; 
 int ROW ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int V_ADP_COLOR ; 
 int V_ADP_FONT ; 
 int V_ADP_MODECHANGE ; 
 int /*<<< orphan*/  dflt_font_14 ; 
 int /*<<< orphan*/  dflt_font_16 ; 
 int /*<<< orphan*/  dflt_font_8 ; 
 int /*<<< orphan*/  ofwfb_set_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ofwfb_static_window ; 
 int /*<<< orphan*/  vid_init_struct (TYPE_2__*,char*,int,int) ; 
 int /*<<< orphan*/  vid_register (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ofwfb_init(int unit, video_adapter_t *adp, int flags)
{
	struct ofwfb_softc *sc;
	video_info_t *vi;
	int cborder;
	int font_height;

	sc = (struct ofwfb_softc *)adp;
	vi = &adp->va_info;

	vid_init_struct(adp, "ofwfb", -1, unit);

	/* The default font size can be overridden by loader */
	font_height = 16;
	TUNABLE_INT_FETCH("hw.syscons.fsize", &font_height);
	if (font_height == 8) {
		sc->sc_font = dflt_font_8;
		sc->sc_font_height = 8;
	} else if (font_height == 14) {
		sc->sc_font = dflt_font_14;
		sc->sc_font_height = 14;
	} else {
		/* default is 8x16 */
		sc->sc_font = dflt_font_16;
		sc->sc_font_height = 16;
	}

	/* The user can set a border in chars - default is 1 char width */
	cborder = 1;
	TUNABLE_INT_FETCH("hw.syscons.border", &cborder);

	vi->vi_cheight = sc->sc_font_height;
	vi->vi_width = sc->sc_width/8 - 2*cborder;
	vi->vi_height = sc->sc_height/sc->sc_font_height - 2*cborder;
	vi->vi_cwidth = 8;

	/*
	 * Clamp width/height to syscons maximums
	 */
	if (vi->vi_width > COL)
		vi->vi_width = COL;
	if (vi->vi_height > ROW)
		vi->vi_height = ROW;

	sc->sc_xmargin = (sc->sc_width - (vi->vi_width * vi->vi_cwidth)) / 2;
	sc->sc_ymargin = (sc->sc_height - (vi->vi_height * vi->vi_cheight))/2;

	/*
	 * Avoid huge amounts of conditional code in syscons by
	 * defining a dummy h/w text display buffer.
	 */
	adp->va_window = (vm_offset_t) ofwfb_static_window;

	/*
	 * Enable future font-loading and flag color support, as well as
	 * adding V_ADP_MODECHANGE so that we ofwfb_set_mode() gets called
	 * when the X server shuts down. This enables us to get the console
	 * back when X disappears.
	 */
	adp->va_flags |= V_ADP_FONT | V_ADP_COLOR | V_ADP_MODECHANGE;

	ofwfb_set_mode(&sc->sc_va, 0);

	vid_register(&sc->sc_va);

	return (0);
}