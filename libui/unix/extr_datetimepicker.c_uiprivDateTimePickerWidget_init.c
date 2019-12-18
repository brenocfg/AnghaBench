#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {void* hasDate; void* hasTime; int /*<<< orphan*/ * mouse; int /*<<< orphan*/ * keyboard; void* toggledSignal; struct TYPE_20__* window; struct TYPE_20__* box; struct TYPE_20__* ampm; struct TYPE_20__* timebox; int /*<<< orphan*/  ampmBlock; struct TYPE_20__* seconds; int /*<<< orphan*/  secondsBlock; struct TYPE_20__* minutes; int /*<<< orphan*/  minutesBlock; struct TYPE_20__* hours; int /*<<< orphan*/  hoursBlock; struct TYPE_20__* calendar; void* calendarBlock; } ;
typedef  TYPE_1__ uiprivDateTimePickerWidget ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GDK_WINDOW_TYPE_HINT_COMBO ; 
 int /*<<< orphan*/  GTK_ALIGN_CENTER ; 
 int /*<<< orphan*/  GTK_COMBO_BOX_TEXT (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_CONTAINER (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_ORIENTATION_HORIZONTAL ; 
 int /*<<< orphan*/  GTK_ORIENTATION_VERTICAL ; 
 int /*<<< orphan*/  GTK_SPIN_BUTTON (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_WIDGET (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_WINDOW (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_WINDOW_POPUP ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 int /*<<< orphan*/ * ampmSpinboxInput ; 
 int /*<<< orphan*/  ampmSpinboxOutput ; 
 int /*<<< orphan*/  buttonReleased ; 
 int /*<<< orphan*/  dateChanged ; 
 int /*<<< orphan*/  g_date_time_new_now_local () ; 
 void* g_signal_connect (TYPE_1__*,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  grabBroken ; 
 void* gtk_box_new (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* gtk_calendar_new () ; 
 int /*<<< orphan*/  gtk_combo_box_text_append (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* gtk_combo_box_text_new () ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_container_set_border_width (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* gtk_label_new (char*) ; 
 int /*<<< orphan*/  gtk_spin_button_set_numeric (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_style_context_add_class (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_widget_get_style_context (TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_widget_set_valign (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_show_all (TYPE_1__*) ; 
 TYPE_1__* gtk_window_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_set_attached_to (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_set_decorated (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_set_deletable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_set_has_resize_grip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_set_resizable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_set_skip_pager_hint (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  gtk_window_set_skip_taskbar_hint (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  gtk_window_set_type_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hoursSpinboxInput ; 
 int /*<<< orphan*/  hoursSpinboxOutput ; 
 void* newSpinbox (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  onToggled ; 
 int /*<<< orphan*/  uiprivDateTimePickerWidget_setTime (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zeroPadSpinbox ; 

__attribute__((used)) static void uiprivDateTimePickerWidget_init(uiprivDateTimePickerWidget *d)
{
	d->window = gtk_window_new(GTK_WINDOW_POPUP);
	gtk_window_set_resizable(GTK_WINDOW(d->window), FALSE);
	gtk_window_set_attached_to(GTK_WINDOW(d->window), GTK_WIDGET(d));
	gtk_window_set_decorated(GTK_WINDOW(d->window), FALSE);
	gtk_window_set_deletable(GTK_WINDOW(d->window), FALSE);
	gtk_window_set_type_hint(GTK_WINDOW(d->window), GDK_WINDOW_TYPE_HINT_COMBO);
	gtk_window_set_skip_taskbar_hint(GTK_WINDOW(d->window), TRUE);
	gtk_window_set_skip_pager_hint(GTK_WINDOW(d->window), TRUE);
	gtk_window_set_has_resize_grip(GTK_WINDOW(d->window), FALSE);
	gtk_container_set_border_width(GTK_CONTAINER(d->window), 12);
	// and make it stand out a bit
	gtk_style_context_add_class(gtk_widget_get_style_context(d->window), "frame");

	d->box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
	gtk_container_add(GTK_CONTAINER(d->window), d->box);

	d->calendar = gtk_calendar_new();
	d->calendarBlock = g_signal_connect(d->calendar, "day-selected", G_CALLBACK(dateChanged), d);
	gtk_container_add(GTK_CONTAINER(d->box), d->calendar);

	d->timebox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
	gtk_widget_set_valign(d->timebox, GTK_ALIGN_CENTER);
	gtk_container_add(GTK_CONTAINER(d->box), d->timebox);

	d->hours = newSpinbox(d, 0, 11, hoursSpinboxInput, hoursSpinboxOutput, &(d->hoursBlock));
	gtk_container_add(GTK_CONTAINER(d->timebox), d->hours);

	gtk_container_add(GTK_CONTAINER(d->timebox),
		gtk_label_new(":"));

	d->minutes = newSpinbox(d, 0, 59, NULL, zeroPadSpinbox, &(d->minutesBlock));
	gtk_container_add(GTK_CONTAINER(d->timebox), d->minutes);

	gtk_container_add(GTK_CONTAINER(d->timebox),
		gtk_label_new(":"));

	d->seconds = newSpinbox(d, 0, 59, NULL, zeroPadSpinbox, &(d->secondsBlock));
	gtk_container_add(GTK_CONTAINER(d->timebox), d->seconds);

	// LONGTERM this should be the case, but that interferes with grabs
	// switch to it when we can drop GTK+ 3.10 and use popovers
#if 0
	d->ampm = gtk_combo_box_text_new();
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(d->ampm), NULL, "AM");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(d->ampm), NULL, "PM");
#endif
	d->ampm = newSpinbox(d, 0, 1, ampmSpinboxInput, ampmSpinboxOutput, &(d->ampmBlock));
	gtk_spin_button_set_numeric(GTK_SPIN_BUTTON(d->ampm), FALSE);
	gtk_widget_set_valign(d->ampm, GTK_ALIGN_CENTER);
	gtk_container_add(GTK_CONTAINER(d->timebox), d->ampm);

	gtk_widget_show_all(d->box);

	g_signal_connect(d->window, "grab-broken-event", G_CALLBACK(grabBroken), d);
	g_signal_connect(d->window, "button-release-event", G_CALLBACK(buttonReleased), d);

	d->toggledSignal = g_signal_connect(d, "toggled", G_CALLBACK(onToggled), NULL);
	d->keyboard = NULL;
	d->mouse = NULL;

	d->hasTime = TRUE;
	d->hasDate = TRUE;

	// set the current date/time
	uiprivDateTimePickerWidget_setTime(d, g_date_time_new_now_local());
}