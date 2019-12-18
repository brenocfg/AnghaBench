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
struct psm_softc {int /*<<< orphan*/  kbdc; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FALSE ; 
 int KBD_AUX_CONTROL_BITS ; 
 int KBD_KBD_CONTROL_BITS ; 
 int /*<<< orphan*/  empty_aux_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbdc_get_device_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbdc_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_controller_command_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
unblock_mouse_data(struct psm_softc *sc, int c)
{
	int error = 0;

	/*
	 * We may have seen a part of status data during `set_mouse_XXX()'.
	 * they have been queued; flush it.
	 */
	empty_aux_buffer(sc->kbdc, 0);

	/* restore ports and interrupt */
	if (!set_controller_command_byte(sc->kbdc,
	    kbdc_get_device_mask(sc->kbdc),
	    c & (KBD_KBD_CONTROL_BITS | KBD_AUX_CONTROL_BITS))) {
		/*
		 * CONTROLLER ERROR; this is serious, we may have
		 * been left with the inaccessible keyboard and
		 * the disabled mouse interrupt.
		 */
		error = EIO;
	}

	kbdc_lock(sc->kbdc, FALSE);
	return (error);
}