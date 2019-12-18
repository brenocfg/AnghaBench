#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ kb_data; } ;
typedef  TYPE_1__ keyboard_t ;
struct TYPE_6__ {int ks_flags; scalar_t__ ks_composed_char; int /*<<< orphan*/  kbdc; } ;
typedef  TYPE_2__ atkbd_state_t ;

/* Variables and functions */
 int COMPOSE ; 
 int FALSE ; 
 int /*<<< orphan*/  KBD_IS_ACTIVE (TYPE_1__*) ; 
 int TRUE ; 
 int kbdc_data_ready (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
atkbd_check_char(keyboard_t *kbd)
{
	atkbd_state_t *state;

	if (!KBD_IS_ACTIVE(kbd))
		return FALSE;
	state = (atkbd_state_t *)kbd->kb_data;
	if (!(state->ks_flags & COMPOSE) && (state->ks_composed_char > 0))
		return TRUE;
	return kbdc_data_ready(state->kbdc);
}