#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_adapter_t ;
struct ofwfb_softc {int sc_depth; int /*<<< orphan*/  sc_va; int /*<<< orphan*/  sc_node; } ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  ihandle_t ;
struct TYPE_2__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;

/* Variables and functions */
 int /*<<< orphan*/  OF_call_method (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  OF_open (char*) ; 
 int /*<<< orphan*/  OF_package_to_path (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  V_DISPLAY_ON ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ofwfb_blank_display (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ofwfb_cmap ; 
 scalar_t__ ofwfb_reset_on_switch ; 

__attribute__((used)) static int
ofwfb_set_mode(video_adapter_t *adp, int mode)
{
	struct ofwfb_softc *sc;
	char name[64];
	ihandle_t ih;
	int i, retval;

	sc = (struct ofwfb_softc *)adp;

	if (ofwfb_reset_on_switch) {
		/*
		 * Open the display device, which will initialize it.
		 */

		memset(name, 0, sizeof(name));
		OF_package_to_path(sc->sc_node, name, sizeof(name));
		ih = OF_open(name);

		if (sc->sc_depth == 8) {
			/*
			 * Install the ISO6429 colormap - older OFW systems
			 * don't do this by default
			 */
			for (i = 0; i < 16; i++) {
				OF_call_method("color!", ih, 4, 1,
						   ofwfb_cmap[i].red,
						   ofwfb_cmap[i].green,
						   ofwfb_cmap[i].blue,
						   i,
						   &retval);
			}
		}
	}

	ofwfb_blank_display(&sc->sc_va, V_DISPLAY_ON);

	return (0);
}