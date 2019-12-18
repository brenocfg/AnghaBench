#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vkbd_state_t ;
struct TYPE_4__ {scalar_t__ kb_data; } ;
typedef  TYPE_1__ keyboard_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  KBD_IS_ACTIVE (TYPE_1__*) ; 
 int /*<<< orphan*/  VKBD_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VKBD_UNLOCK (int /*<<< orphan*/ *) ; 
 int vkbd_data_ready (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vkbd_check(keyboard_t *kbd)
{
	vkbd_state_t	*state = NULL;
	int		 ready;

	if (!KBD_IS_ACTIVE(kbd))
		return (FALSE);

	state = (vkbd_state_t *) kbd->kb_data;

	VKBD_LOCK(state);
	ready = vkbd_data_ready(state);
	VKBD_UNLOCK(state);

	return (ready);
}