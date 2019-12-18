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
struct TYPE_5__ {int vi_cheight; int vi_cwidth; int vi_width; int vi_height; } ;
typedef  TYPE_1__ video_info_t ;
struct TYPE_6__ {int /*<<< orphan*/  va_flags; scalar_t__ va_window; TYPE_1__ va_info; } ;
typedef  TYPE_2__ video_adapter_t ;
struct video_adapter_softc {int width; int height; int xmargin; int ymargin; int /*<<< orphan*/  va; int /*<<< orphan*/  font; } ;

/* Variables and functions */
 int COL ; 
 int ROW ; 
 int VERSATILE_FONT_HEIGHT ; 
 int /*<<< orphan*/  V_ADP_FONT ; 
 int /*<<< orphan*/  dflt_font_16 ; 
 scalar_t__ versatilefb_static_window ; 
 int /*<<< orphan*/  vid_init_struct (TYPE_2__*,char*,int,int) ; 
 int /*<<< orphan*/  vid_register (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
versatilefb_init(int unit, video_adapter_t *adp, int flags)
{
	struct video_adapter_softc *sc;
	video_info_t *vi;

	sc = (struct video_adapter_softc *)adp;
	vi = &adp->va_info;

	vid_init_struct(adp, "versatilefb", -1, unit);

	sc->font = dflt_font_16;
	vi->vi_cheight = VERSATILE_FONT_HEIGHT;
	vi->vi_cwidth = 8;

	vi->vi_width = sc->width/8;
	vi->vi_height = sc->height/vi->vi_cheight;

	/*
	 * Clamp width/height to syscons maximums
	 */
	if (vi->vi_width > COL)
		vi->vi_width = COL;
	if (vi->vi_height > ROW)
		vi->vi_height = ROW;

	sc->xmargin = (sc->width - (vi->vi_width * vi->vi_cwidth)) / 2;
	sc->ymargin = (sc->height - (vi->vi_height * vi->vi_cheight))/2;

	adp->va_window = (vm_offset_t) versatilefb_static_window;
	adp->va_flags |= V_ADP_FONT /* | V_ADP_COLOR | V_ADP_MODECHANGE */;

	vid_register(&sc->va);

	return (0);
}