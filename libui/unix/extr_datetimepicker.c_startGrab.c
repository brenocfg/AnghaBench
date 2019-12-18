#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * mouse; int /*<<< orphan*/ * keyboard; int /*<<< orphan*/  window; } ;
typedef  TYPE_1__ uiprivDateTimePickerWidget ;
typedef  int /*<<< orphan*/  guint32 ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_8__ {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  GdkWindow ;
typedef  int /*<<< orphan*/  GdkDisplay ;
typedef  int /*<<< orphan*/  GdkDeviceManager ;
typedef  int /*<<< orphan*/  GdkDevice ;
typedef  TYPE_2__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int GDK_BUTTON_PRESS_MASK ; 
 int GDK_BUTTON_RELEASE_MASK ; 
 int /*<<< orphan*/  GDK_DEVICE_TYPE_MASTER ; 
 scalar_t__ GDK_GRAB_SUCCESS ; 
 int GDK_KEY_PRESS_MASK ; 
 int GDK_KEY_RELEASE_MASK ; 
 int /*<<< orphan*/  GDK_OWNERSHIP_WINDOW ; 
 int GDK_POINTER_MOTION_MASK ; 
 scalar_t__ GDK_SOURCE_KEYBOARD ; 
 int /*<<< orphan*/  GTK_WIDGET (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_list_free (TYPE_2__*) ; 
 int /*<<< orphan*/ * gdk_device_get_associated_device (int /*<<< orphan*/ *) ; 
 scalar_t__ gdk_device_get_source (int /*<<< orphan*/ *) ; 
 scalar_t__ gdk_device_grab (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* gdk_device_manager_list_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdk_device_ungrab (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gdk_display_get_device_manager (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_device_grab_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_get_current_event_device () ; 
 int /*<<< orphan*/  gtk_get_current_event_time () ; 
 int /*<<< orphan*/ * gtk_widget_get_display (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_widget_get_window (int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean startGrab(uiprivDateTimePickerWidget *d)
{
	GdkDevice *dev;
	guint32 time;
	GdkWindow *window;
	GdkDevice *keyboard, *mouse;

	dev = gtk_get_current_event_device();
	if (dev == NULL) {
		// this is what GtkComboBox does
		// since no device was set, just use the first available "master device"
		GdkDisplay *disp;
		GdkDeviceManager *dm;
		GList *list;

		disp = gtk_widget_get_display(GTK_WIDGET(d));
		dm = gdk_display_get_device_manager(disp);
		list = gdk_device_manager_list_devices(dm, GDK_DEVICE_TYPE_MASTER);
		dev = (GdkDevice *) (list->data);
		g_list_free(list);
	}

	time = gtk_get_current_event_time();
	keyboard = dev;
	mouse = gdk_device_get_associated_device(dev);
	if (gdk_device_get_source(dev) != GDK_SOURCE_KEYBOARD) {
		dev = mouse;
		mouse = keyboard;
		keyboard = dev;
	}

	window = gtk_widget_get_window(d->window);
	if (keyboard != NULL)
		if (gdk_device_grab(keyboard, window,
			GDK_OWNERSHIP_WINDOW, TRUE,
			GDK_KEY_PRESS_MASK | GDK_KEY_RELEASE_MASK,
			NULL, time) != GDK_GRAB_SUCCESS)
			return FALSE;
	if (mouse != NULL)
		if (gdk_device_grab(mouse, window,
			GDK_OWNERSHIP_WINDOW, TRUE,
			GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK | GDK_POINTER_MOTION_MASK,
			NULL, time) != GDK_GRAB_SUCCESS) {
			if (keyboard != NULL)
				gdk_device_ungrab(keyboard, time);
			return FALSE;
		}

	gtk_device_grab_add(d->window, mouse, TRUE);
	d->keyboard = keyboard;
	d->mouse = mouse;
	return TRUE;
}