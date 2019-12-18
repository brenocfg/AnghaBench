#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int sizex; int sizey; scalar_t__ isclickpad; scalar_t__ issemimt; int /*<<< orphan*/  hastrackpoint; int /*<<< orphan*/  dpmmy; int /*<<< orphan*/  dpmmx; int /*<<< orphan*/  fwversion; int /*<<< orphan*/  hwversion; } ;
struct TYPE_5__ {int max_x; int max_y; int min_pressure; int max_width; int tap_min_queue; int weight_len_squared; int div_min; int div_max; int div_max_na; int div_len; int tap_max_delta; int vscroll_min_delta; int vscroll_div_min; int vscroll_div_max; int softbuttons_y; int softbutton2_x; int softbutton3_x; scalar_t__ vscroll_ver_area; scalar_t__ vscroll_hor_area; scalar_t__ na_left; scalar_t__ na_bottom; scalar_t__ na_right; scalar_t__ na_top; scalar_t__ margin_left; scalar_t__ margin_bottom; scalar_t__ margin_right; scalar_t__ margin_top; int /*<<< orphan*/ * sysctl_tree; } ;
struct TYPE_4__ {int nExtendedQueries; int capExtended; int capMultiFinger; int capAdvancedGestures; int capReportsV; int capPalmDetect; int capReportsMax; int maximumXCoord; int maximumYCoord; int capReportsMin; scalar_t__ minimumYCoord; scalar_t__ minimumXCoord; scalar_t__ capPen; scalar_t__ capClickPad; int /*<<< orphan*/  capPassthrough; scalar_t__ verticalScroll; int /*<<< orphan*/  infoYupmm; int /*<<< orphan*/  infoXupmm; int /*<<< orphan*/  infoMinor; int /*<<< orphan*/  infoMajor; } ;
struct psm_softc {TYPE_3__ elanhw; TYPE_2__ syninfo; TYPE_1__ synhw; } ;

/* Variables and functions */
 int /*<<< orphan*/  synaptics_sysctl_create_tree (struct psm_softc*,char*,char*) ; 

__attribute__((used)) static void
elantech_init_synaptics(struct psm_softc *sc)
{

	/* Set capabilites required by movement smother */
	sc->synhw.infoMajor = sc->elanhw.hwversion;
	sc->synhw.infoMinor = sc->elanhw.fwversion;
	sc->synhw.infoXupmm = sc->elanhw.dpmmx;
	sc->synhw.infoYupmm = sc->elanhw.dpmmy;
	sc->synhw.verticalScroll = 0;
	sc->synhw.nExtendedQueries = 4;
	sc->synhw.capExtended = 1;
	sc->synhw.capPassthrough = sc->elanhw.hastrackpoint;
	sc->synhw.capClickPad = sc->elanhw.isclickpad;
	sc->synhw.capMultiFinger = 1;
	if (sc->elanhw.issemimt)
		sc->synhw.capAdvancedGestures = 1;
	else
		sc->synhw.capReportsV = 1;
	sc->synhw.capPalmDetect = 1;
	sc->synhw.capPen = 0;
	sc->synhw.capReportsMax = 1;
	sc->synhw.maximumXCoord = sc->elanhw.sizex;
	sc->synhw.maximumYCoord = sc->elanhw.sizey;
	sc->synhw.capReportsMin = 1;
	sc->synhw.minimumXCoord = 0;
	sc->synhw.minimumYCoord = 0;

	if (sc->syninfo.sysctl_tree == NULL) {
		synaptics_sysctl_create_tree(sc, "elantech",
		    "Elantech Touchpad");

		/*
		 * Adjust synaptic smoother tunables
		 * 1. Disable finger detection pressure threshold. Unlike
		 *    synaptics we assume the finger is acting when packet with
		 *    its X&Y arrives not when pressure exceedes some threshold
		 * 2. Disable unrelated features like margins and noisy areas
		 * 3. Disable virtual scroll areas as 2nd finger is preferable
		 * 4. For clickpads set bottom quarter as 42% - 16% - 42% sized
		 *    softbuttons
		 * 5. Scale down divisors and movement lengths by a factor of 3
		 *    where 3 is Synaptics to Elantech (~2200/800) dpi ratio
		 */

		/* Set reporting range to be equal touchpad size */
		sc->syninfo.max_x = sc->elanhw.sizex;
		sc->syninfo.max_y = sc->elanhw.sizey;

		/* Disable finger detection pressure threshold */
		sc->syninfo.min_pressure = 1;

		/* Adjust palm width to nearly match synaptics w=10 */
		sc->syninfo.max_width = 7;

		/* Elans often report double & triple taps as single event */
		sc->syninfo.tap_min_queue = 1;

		/* Use full area of touchpad */
		sc->syninfo.margin_top = 0;
		sc->syninfo.margin_right = 0;
		sc->syninfo.margin_bottom = 0;
		sc->syninfo.margin_left = 0;

		/* Disable noisy area */
		sc->syninfo.na_top = 0;
		sc->syninfo.na_right = 0;
		sc->syninfo.na_bottom = 0;
		sc->syninfo.na_left = 0;

		/* Tune divisors and movement lengths */
		sc->syninfo.weight_len_squared = 200;
		sc->syninfo.div_min = 3;
		sc->syninfo.div_max = 6;
		sc->syninfo.div_max_na = 10;
		sc->syninfo.div_len = 30;
		sc->syninfo.tap_max_delta = 25;

		/* Disable virtual scrolling areas and tune its divisors */
		sc->syninfo.vscroll_hor_area = 0;
		sc->syninfo.vscroll_ver_area = 0;
		sc->syninfo.vscroll_min_delta = 15;
		sc->syninfo.vscroll_div_min = 30;
		sc->syninfo.vscroll_div_max = 50;

		/* Set bottom quarter as 42% - 16% - 42% sized softbuttons */
		if (sc->elanhw.isclickpad) {
			sc->syninfo.softbuttons_y = sc->elanhw.sizey / 4;
			sc->syninfo.softbutton2_x = sc->elanhw.sizex * 11 / 25;
			sc->syninfo.softbutton3_x = sc->elanhw.sizex * 14 / 25;
		}
	}

	return;
}