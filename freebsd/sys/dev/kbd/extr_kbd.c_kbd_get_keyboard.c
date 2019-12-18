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
typedef  int /*<<< orphan*/  keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  KBD_IS_VALID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** keyboard ; 
 int keyboards ; 

keyboard_t *
kbd_get_keyboard(int index)
{
	if ((index < 0) || (index >= keyboards))
		return (NULL);
	if (keyboard[index] == NULL)
		return (NULL);
	if (!KBD_IS_VALID(keyboard[index]))
		return (NULL);
	return (keyboard[index]);
}