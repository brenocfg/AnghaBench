#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ model; } ;
struct TYPE_3__ {scalar_t__ capReportsV; scalar_t__ capAdvancedGestures; } ;
struct psm_softc {int /*<<< orphan*/  kbdc; TYPE_2__ hw; TYPE_1__ synhw; } ;

/* Variables and functions */
 scalar_t__ MOUSE_MODEL_SYNAPTICS ; 
 int SYNAPTICS_READ_MODEL_ID ; 
 int /*<<< orphan*/  mouse_ext_command (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_mouse_sampling_rate (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
synaptics_set_mode(struct psm_softc *sc, int mode_byte) {
	mouse_ext_command(sc->kbdc, mode_byte);

	/* "Commit" the Set Mode Byte command sent above. */
	set_mouse_sampling_rate(sc->kbdc, 20);

	/*
	 * Enable advanced gestures mode if supported and we are not entering
	 * passthrough or relative mode.
	 */
	if ((sc->synhw.capAdvancedGestures || sc->synhw.capReportsV) &&
	    sc->hw.model == MOUSE_MODEL_SYNAPTICS && !(mode_byte & (1 << 5))) {
		mouse_ext_command(sc->kbdc, SYNAPTICS_READ_MODEL_ID);
		set_mouse_sampling_rate(sc->kbdc, 0xc8);
	}
}