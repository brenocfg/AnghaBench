#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ kb_data; } ;
typedef  TYPE_1__ keyboard_t ;
struct TYPE_8__ {int ks_flags; scalar_t__ ks_composed_char; scalar_t__ ks_inq_length; } ;
typedef  TYPE_2__ kbdmux_state_t ;

/* Variables and functions */
 int COMPOSE ; 
 int FALSE ; 
 int /*<<< orphan*/  KBDMUX_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  KBDMUX_UNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  KBD_IS_ACTIVE (TYPE_1__*) ; 
 int TRUE ; 

__attribute__((used)) static int
kbdmux_check_char(keyboard_t *kbd)
{
	kbdmux_state_t	*state = (kbdmux_state_t *) kbd->kb_data;
	int		 ready;

	if (!KBD_IS_ACTIVE(kbd))
		return (FALSE);

	KBDMUX_LOCK(state);

	if (!(state->ks_flags & COMPOSE) && (state->ks_composed_char != 0))
		ready = TRUE;
	else
		ready = (state->ks_inq_length > 0) ? TRUE : FALSE;

	KBDMUX_UNLOCK(state);

	return (ready);
}