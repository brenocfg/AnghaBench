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
struct TYPE_4__ {int /*<<< orphan*/  kb_count; scalar_t__ kb_data; } ;
typedef  TYPE_1__ keyboard_t ;
typedef  int /*<<< orphan*/  kbdmux_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  KBDMUX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KBDMUX_UNLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ KBD_IS_ACTIVE (TYPE_1__*) ; 
 int kbdmux_kbd_getc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
kbdmux_read(keyboard_t *kbd, int wait)
{
	kbdmux_state_t	*state = (kbdmux_state_t *) kbd->kb_data;
	int		 c;

	KBDMUX_LOCK(state);
	c = kbdmux_kbd_getc(state);
	KBDMUX_UNLOCK(state);

	if (c != -1)
		kbd->kb_count ++;

	return (KBD_IS_ACTIVE(kbd)? c : -1);
}