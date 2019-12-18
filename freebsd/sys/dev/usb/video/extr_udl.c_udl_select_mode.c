#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int edid_nmodes; TYPE_2__* edid_modes; TYPE_1__* edid_preferred_mode; } ;
struct udl_softc {int sc_cur_mode; int /*<<< orphan*/  sc_chip; TYPE_3__ sc_edid_info; int /*<<< orphan*/  sc_edid; } ;
struct udl_mode {int hz; int clock; int hdisplay; int vdisplay; } ;
struct TYPE_6__ {int dot_clock; int htotal; int vtotal; int hdisplay; int vdisplay; } ;
struct TYPE_5__ {int dot_clock; int htotal; int vtotal; int hdisplay; int vdisplay; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int UDL_MAX_MODES ; 
 int /*<<< orphan*/  edid_parse (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  edid_print (TYPE_3__*) ; 
 void* udl_lookup_mode (int,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
udl_select_mode(struct udl_softc *sc)
{
	struct udl_mode mode;
	int index = UDL_MAX_MODES;
	int i;

	/* try to get the preferred mode from EDID */
	edid_parse(sc->sc_edid, &sc->sc_edid_info);
#ifdef USB_DEBUG
	edid_print(&sc->sc_edid_info);
#endif
	if (sc->sc_edid_info.edid_preferred_mode != NULL) {
		mode.hz =
		    (sc->sc_edid_info.edid_preferred_mode->dot_clock * 1000) /
		    (sc->sc_edid_info.edid_preferred_mode->htotal *
		    sc->sc_edid_info.edid_preferred_mode->vtotal);
		mode.clock =
		    sc->sc_edid_info.edid_preferred_mode->dot_clock / 10;
		mode.hdisplay =
		    sc->sc_edid_info.edid_preferred_mode->hdisplay;
		mode.vdisplay =
		    sc->sc_edid_info.edid_preferred_mode->vdisplay;
		index = udl_lookup_mode(mode.hdisplay, mode.vdisplay, mode.hz,
		    sc->sc_chip, mode.clock);
		sc->sc_cur_mode = index;
	} else {
		DPRINTF("no preferred mode found!\n");
	}

	if (index == UDL_MAX_MODES) {
		DPRINTF("no mode line found\n");

		i = 0;
		while (i < sc->sc_edid_info.edid_nmodes) {
			mode.hz =
			    (sc->sc_edid_info.edid_modes[i].dot_clock * 1000) /
			    (sc->sc_edid_info.edid_modes[i].htotal *
			    sc->sc_edid_info.edid_modes[i].vtotal);
			mode.clock =
			    sc->sc_edid_info.edid_modes[i].dot_clock / 10;
			mode.hdisplay =
			    sc->sc_edid_info.edid_modes[i].hdisplay;
			mode.vdisplay =
			    sc->sc_edid_info.edid_modes[i].vdisplay;
			index = udl_lookup_mode(mode.hdisplay, mode.vdisplay,
			    mode.hz, sc->sc_chip, mode.clock);
			if (index < UDL_MAX_MODES)
				if ((sc->sc_cur_mode == UDL_MAX_MODES) ||
				    (index > sc->sc_cur_mode))
					sc->sc_cur_mode = index;
			i++;
		}
	}
	/*
	 * If no mode found use default.
	 */
	if (sc->sc_cur_mode == UDL_MAX_MODES)
		sc->sc_cur_mode = udl_lookup_mode(800, 600, 60, sc->sc_chip, 0);
}