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
struct console {int flags; } ;

/* Variables and functions */
 int CON_BRL ; 
 int EINVAL ; 
 struct console* braille_co ; 
 int /*<<< orphan*/  keyboard_notifier_block ; 
 int /*<<< orphan*/  unregister_keyboard_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_vt_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vt_notifier_block ; 

int braille_unregister_console(struct console *console)
{
	if (braille_co != console)
		return -EINVAL;
	if (!(console->flags & CON_BRL))
		return 0;
	unregister_keyboard_notifier(&keyboard_notifier_block);
	unregister_vt_notifier(&vt_notifier_block);
	braille_co = NULL;
	return 1;
}