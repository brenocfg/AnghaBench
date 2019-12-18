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
struct TYPE_4__ {int /*<<< orphan*/  cc; } ;
typedef  TYPE_1__ areaWidget ;

/* Variables and functions */
 int GDK_BUTTON_MOTION_MASK ; 
 int GDK_BUTTON_PRESS_MASK ; 
 int GDK_BUTTON_RELEASE_MASK ; 
 int GDK_ENTER_NOTIFY_MASK ; 
 int GDK_KEY_PRESS_MASK ; 
 int GDK_KEY_RELEASE_MASK ; 
 int GDK_LEAVE_NOTIFY_MASK ; 
 int GDK_POINTER_MOTION_MASK ; 
 int /*<<< orphan*/  GTK_WIDGET (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gtk_widget_add_events (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_widget_set_can_focus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiprivClickCounterReset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void areaWidget_init(areaWidget *aw)
{
	// for events
	gtk_widget_add_events(GTK_WIDGET(aw),
		GDK_POINTER_MOTION_MASK |
		GDK_BUTTON_MOTION_MASK |
		GDK_BUTTON_PRESS_MASK |
		GDK_BUTTON_RELEASE_MASK |
		GDK_KEY_PRESS_MASK |
		GDK_KEY_RELEASE_MASK |
		GDK_ENTER_NOTIFY_MASK |
		GDK_LEAVE_NOTIFY_MASK);

	gtk_widget_set_can_focus(GTK_WIDGET(aw), TRUE);

	uiprivClickCounterReset(&(aw->cc));
}