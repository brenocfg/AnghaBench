#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int ks_flags; struct TYPE_13__* kb_fkeytab; struct TYPE_13__* kb_accentmap; struct TYPE_13__* kb_keymap; int /*<<< orphan*/  ks_evdev; int /*<<< orphan*/ * kbd; int /*<<< orphan*/  ks_kbds; int /*<<< orphan*/  ks_timo; scalar_t__ kb_data; } ;
typedef  TYPE_1__ keyboard_t ;
typedef  TYPE_1__ kbdmux_state_t ;
typedef  TYPE_1__ kbdmux_kbd_t ;

/* Variables and functions */
 int /*<<< orphan*/  KBDMUX_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  KBDMUX_LOCK_DESTROY (TYPE_1__*) ; 
 int /*<<< orphan*/  KBDMUX_SLEEP (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KBDMUX_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  M_KBDMUX ; 
 TYPE_1__* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int TASK ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evdev_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbd_release (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kbd_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  ks_task ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static int
kbdmux_term(keyboard_t *kbd)
{
	kbdmux_state_t	*state = (kbdmux_state_t *) kbd->kb_data;
	kbdmux_kbd_t	*k;

	KBDMUX_LOCK(state);

	/* kill callout */
	callout_stop(&state->ks_timo);

	/* wait for interrupt task */
	while (state->ks_flags & TASK)
		KBDMUX_SLEEP(state, ks_task, "kbdmuxc", 0);

	/* release all keyboards from the mux */
	while ((k = SLIST_FIRST(&state->ks_kbds)) != NULL) {
		kbd_release(k->kbd, &k->kbd);
		SLIST_REMOVE_HEAD(&state->ks_kbds, next);

		k->kbd = NULL;

		free(k, M_KBDMUX);
	}

	KBDMUX_UNLOCK(state);

	kbd_unregister(kbd);

#ifdef EVDEV_SUPPORT
	evdev_free(state->ks_evdev);
#endif

	KBDMUX_LOCK_DESTROY(state);
	bzero(state, sizeof(*state));
	free(state, M_KBDMUX);

	free(kbd->kb_keymap, M_KBDMUX);
	free(kbd->kb_accentmap, M_KBDMUX);
	free(kbd->kb_fkeytab, M_KBDMUX);
	free(kbd, M_KBDMUX);

	return (0);
}