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
struct TYPE_4__ {scalar_t__ capExtended; } ;
struct TYPE_3__ {scalar_t__ model; } ;
struct psm_softc {TYPE_2__ synhw; TYPE_1__ hw; } ;

/* Variables and functions */
 scalar_t__ MOUSE_MODEL_SYNAPTICS ; 
 scalar_t__ tap_enabled ; 

__attribute__((used)) static int
synaptics_preferred_mode(struct psm_softc *sc) {
	int mode_byte;

	/* Check if we are in relative mode */
	if (sc->hw.model != MOUSE_MODEL_SYNAPTICS) {
		if (tap_enabled == 0)
			/*
			 * Disable tap & drag gestures. We use a Mode Byte
			 * and set the DisGest bit (see §2.5 of Synaptics
			 * TouchPad Interfacing Guide).
			 */
			return (0x04);
		else
			/*
			 * Enable tap & drag gestures. We use a Mode Byte
			 * and clear the DisGest bit (see §2.5 of Synaptics
			 * TouchPad Interfacing Guide).
			 */
			return (0x00);
	}

	mode_byte = 0xc4;

	/* request wmode where available */
	if (sc->synhw.capExtended)
		mode_byte |= 1;

	return mode_byte;
}