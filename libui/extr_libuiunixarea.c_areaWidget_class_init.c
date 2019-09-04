#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  areaWidgetClass ;
struct TYPE_5__ {int /*<<< orphan*/  key_release_event; int /*<<< orphan*/  key_press_event; int /*<<< orphan*/  leave_notify_event; int /*<<< orphan*/  enter_notify_event; int /*<<< orphan*/  motion_notify_event; int /*<<< orphan*/  button_release_event; int /*<<< orphan*/  button_press_event; int /*<<< orphan*/  get_preferred_width; int /*<<< orphan*/  get_preferred_height; int /*<<< orphan*/  draw; int /*<<< orphan*/  size_allocate; } ;
struct TYPE_4__ {int /*<<< orphan*/  get_property; int /*<<< orphan*/  set_property; int /*<<< orphan*/  finalize; int /*<<< orphan*/  dispose; } ;

/* Variables and functions */
 TYPE_3__* GTK_WIDGET_CLASS (int /*<<< orphan*/ *) ; 
 TYPE_1__* G_OBJECT_CLASS (int /*<<< orphan*/ *) ; 
 int G_PARAM_CONSTRUCT_ONLY ; 
 int G_PARAM_STATIC_STRINGS ; 
 int G_PARAM_WRITABLE ; 
 int /*<<< orphan*/  areaWidget_button_press_event ; 
 int /*<<< orphan*/  areaWidget_button_release_event ; 
 int /*<<< orphan*/  areaWidget_dispose ; 
 int /*<<< orphan*/  areaWidget_draw ; 
 int /*<<< orphan*/  areaWidget_enter_notify_event ; 
 int /*<<< orphan*/  areaWidget_finalize ; 
 int /*<<< orphan*/  areaWidget_get_preferred_height ; 
 int /*<<< orphan*/  areaWidget_get_preferred_width ; 
 int /*<<< orphan*/  areaWidget_get_property ; 
 int /*<<< orphan*/  areaWidget_key_press_event ; 
 int /*<<< orphan*/  areaWidget_key_release_event ; 
 int /*<<< orphan*/  areaWidget_leave_notify_event ; 
 int /*<<< orphan*/  areaWidget_motion_notify_event ; 
 int /*<<< orphan*/  areaWidget_set_property ; 
 int /*<<< orphan*/  areaWidget_size_allocate ; 
 int /*<<< orphan*/  g_object_class_install_property (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_param_spec_pointer (char*,char*,char*,int) ; 
 int /*<<< orphan*/  pArea ; 
 int /*<<< orphan*/  pspecArea ; 

__attribute__((used)) static void areaWidget_class_init(areaWidgetClass *class)
{
	G_OBJECT_CLASS(class)->dispose = areaWidget_dispose;
	G_OBJECT_CLASS(class)->finalize = areaWidget_finalize;
	G_OBJECT_CLASS(class)->set_property = areaWidget_set_property;
	G_OBJECT_CLASS(class)->get_property = areaWidget_get_property;

	GTK_WIDGET_CLASS(class)->size_allocate = areaWidget_size_allocate;
	GTK_WIDGET_CLASS(class)->draw = areaWidget_draw;
	GTK_WIDGET_CLASS(class)->get_preferred_height = areaWidget_get_preferred_height;
	GTK_WIDGET_CLASS(class)->get_preferred_width = areaWidget_get_preferred_width;
	GTK_WIDGET_CLASS(class)->button_press_event = areaWidget_button_press_event;
	GTK_WIDGET_CLASS(class)->button_release_event = areaWidget_button_release_event;
	GTK_WIDGET_CLASS(class)->motion_notify_event = areaWidget_motion_notify_event;
	GTK_WIDGET_CLASS(class)->enter_notify_event = areaWidget_enter_notify_event;
	GTK_WIDGET_CLASS(class)->leave_notify_event = areaWidget_leave_notify_event;
	GTK_WIDGET_CLASS(class)->key_press_event = areaWidget_key_press_event;
	GTK_WIDGET_CLASS(class)->key_release_event = areaWidget_key_release_event;

	pspecArea = g_param_spec_pointer("libui-area",
		"libui-area",
		"uiArea.",
		G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY | G_PARAM_STATIC_STRINGS);
	g_object_class_install_property(G_OBJECT_CLASS(class), pArea, pspecArea);
}