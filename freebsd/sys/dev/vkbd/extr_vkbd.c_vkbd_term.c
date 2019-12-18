#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* kb_fkeytab; struct TYPE_8__* kb_accentmap; struct TYPE_8__* kb_keymap; scalar_t__ kb_data; } ;
typedef  TYPE_1__ vkbd_state_t ;
typedef  TYPE_1__ keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_VKBD ; 
 int /*<<< orphan*/  VKBD_LOCK_DESTROY (TYPE_1__*) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbd_unregister (TYPE_1__*) ; 

__attribute__((used)) static int
vkbd_term(keyboard_t *kbd)
{
	vkbd_state_t	*state = (vkbd_state_t *) kbd->kb_data;

	kbd_unregister(kbd);

	VKBD_LOCK_DESTROY(state);
	bzero(state, sizeof(*state));
	free(state, M_VKBD);

	free(kbd->kb_keymap, M_VKBD);
	free(kbd->kb_accentmap, M_VKBD);
	free(kbd->kb_fkeytab, M_VKBD);
	free(kbd, M_VKBD);

	return (0);
}