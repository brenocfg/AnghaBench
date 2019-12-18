#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vkbd_state_t ;
struct TYPE_3__ {scalar_t__ kb_data; } ;
typedef  TYPE_1__ keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  VKBD_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VKBD_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkbd_clear_state_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vkbd_clear_state(keyboard_t *kbd)
{
	vkbd_state_t	*state = (vkbd_state_t *) kbd->kb_data;

	VKBD_LOCK(state);
	vkbd_clear_state_locked(state);
	VKBD_UNLOCK(state);
}