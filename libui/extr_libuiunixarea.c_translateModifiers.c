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
typedef  int /*<<< orphan*/  guint ;
typedef  int /*<<< orphan*/  GdkWindow ;
typedef  int /*<<< orphan*/  GdkModifierType ;

/* Variables and functions */
 int /*<<< orphan*/  gdk_keymap_add_virtual_modifiers (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdk_keymap_get_for_display (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_window_get_display (int /*<<< orphan*/ *) ; 

__attribute__((used)) static guint translateModifiers(guint state, GdkWindow *window)
{
	GdkModifierType statetype;

	// GDK doesn't initialize the modifier flags fully; we have to explicitly tell it to (thanks to Daniel_S and daniels (two different people) in irc.gimp.net/#gtk+)
	statetype = state;
	gdk_keymap_add_virtual_modifiers(
		gdk_keymap_get_for_display(gdk_window_get_display(window)),
		&statetype);
	return statetype;
}