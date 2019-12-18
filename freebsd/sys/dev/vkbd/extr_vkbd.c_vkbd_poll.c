#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ks_polling; } ;
typedef  TYPE_1__ vkbd_state_t ;
struct TYPE_7__ {scalar_t__ kb_data; } ;
typedef  TYPE_2__ keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  VKBD_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  VKBD_UNLOCK (TYPE_1__*) ; 

__attribute__((used)) static int
vkbd_poll(keyboard_t *kbd, int on)
{
	vkbd_state_t	*state = NULL;

	state = (vkbd_state_t *) kbd->kb_data;

	VKBD_LOCK(state);

	if (on)
		state->ks_polling ++;
	else
		state->ks_polling --;

	VKBD_UNLOCK(state);

	return (0);
}