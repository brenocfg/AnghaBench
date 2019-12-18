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
typedef  int /*<<< orphan*/  uiModifiers ;
typedef  int guint ;

/* Variables and functions */
 int GDK_CONTROL_MASK ; 
 int GDK_META_MASK ; 
 int GDK_MOD1_MASK ; 
 int GDK_SHIFT_MASK ; 
 int GDK_SUPER_MASK ; 
 int /*<<< orphan*/  uiModifierAlt ; 
 int /*<<< orphan*/  uiModifierCtrl ; 
 int /*<<< orphan*/  uiModifierShift ; 
 int /*<<< orphan*/  uiModifierSuper ; 

__attribute__((used)) static uiModifiers toModifiers(guint state)
{
	uiModifiers m;

	m = 0;
	if ((state & GDK_CONTROL_MASK) != 0)
		m |= uiModifierCtrl;
	if ((state & GDK_META_MASK) != 0)
		m |= uiModifierAlt;
	if ((state & GDK_MOD1_MASK) != 0)		// GTK+ itself requires this to be Alt (just read through gtkaccelgroup.c)
		m |= uiModifierAlt;
	if ((state & GDK_SHIFT_MASK) != 0)
		m |= uiModifierShift;
	if ((state & GDK_SUPER_MASK) != 0)
		m |= uiModifierSuper;
	return m;
}