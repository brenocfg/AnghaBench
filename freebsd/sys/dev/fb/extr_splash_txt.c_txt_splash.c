#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int vi_flags; } ;
struct TYPE_13__ {size_t va_index; TYPE_1__ va_info; } ;
typedef  TYPE_2__ video_adapter_t ;
struct TYPE_14__ {int /*<<< orphan*/  scr; } ;
typedef  TYPE_3__ scr_stat ;
struct TYPE_15__ {int /*<<< orphan*/ * scr_map; TYPE_3__* cur_scp; } ;
typedef  TYPE_4__ sc_softc_t ;
struct TYPE_16__ {int /*<<< orphan*/  (* set_hw_cursor ) (TYPE_2__*,int,int) ;} ;

/* Variables and functions */
 int BG_BLACK ; 
 int EAGAIN ; 
 scalar_t__ FALSE ; 
 int FG_LIGHTGREY ; 
 scalar_t__ TRUE ; 
 int V_INFO_GRAPHICS ; 
 int /*<<< orphan*/  draw_text_splash (TYPE_4__*) ; 
 TYPE_4__* sc_find_softc (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sc_set_border (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_vtb_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ splash_on ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int,int) ; 
 TYPE_5__** vidsw ; 

__attribute__((used)) static int
txt_splash(video_adapter_t *adp, const int on)
{
	sc_softc_t *sc;
	scr_stat *scp;

	sc = sc_find_softc(adp, NULL);
	if (sc == NULL)
		return (EAGAIN);
	scp = sc->cur_scp;
	if (on) {
		if (!splash_on) {
			if (adp->va_info.vi_flags & V_INFO_GRAPHICS)
				return EAGAIN;
			/* Clear screen and set border colour. */
			sc_vtb_clear(&scp->scr, sc->scr_map[0x20],
			    (FG_LIGHTGREY | BG_BLACK) << 8);
			(*vidsw[adp->va_index]->set_hw_cursor)(adp, -1, -1);
			sc_set_border(scp, 0);
			splash_on = TRUE;
			/* Display the splash screen. */
			draw_text_splash(sc);
		}
		return (0);
	} else {
		/* The video mode will be restored by the caller. */
		splash_on = FALSE;
		return (0);
	}
}