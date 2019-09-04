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
struct TYPE_3__ {int /*<<< orphan*/  secondsBlock; int /*<<< orphan*/  seconds; int /*<<< orphan*/  minutesBlock; int /*<<< orphan*/  minutes; int /*<<< orphan*/  hoursBlock; int /*<<< orphan*/  hours; int /*<<< orphan*/  ampmBlock; int /*<<< orphan*/  ampm; scalar_t__ hasTime; int /*<<< orphan*/  calendarBlock; int /*<<< orphan*/  calendar; scalar_t__ hasDate; } ;
typedef  TYPE_1__ uiprivDateTimePickerWidget ;
typedef  int gint ;
typedef  int /*<<< orphan*/  GDateTime ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_CALENDAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_SPIN_BUTTON (int /*<<< orphan*/ ) ; 
 int g_date_time_get_hour (int /*<<< orphan*/ *) ; 
 int g_date_time_get_minute (int /*<<< orphan*/ *) ; 
 int g_date_time_get_seconds (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_date_time_get_ymd (int /*<<< orphan*/ *,int*,int*,int*) ; 
 int /*<<< orphan*/  g_date_time_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_handler_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_handler_unblock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_calendar_select_day (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_calendar_select_month (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  setRealSpinValue (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uiprivDateTimePickerWidget_setTime(uiprivDateTimePickerWidget *d, GDateTime *dt)
{
	gint year, month, day;
	gint hour;

	// notice how we block signals from firing
	if (d->hasDate) {
		g_date_time_get_ymd(dt, &year, &month, &day);
		month--;			// GDateTime/GtkCalendar differences
		g_signal_handler_block(d->calendar, d->calendarBlock);
		gtk_calendar_select_month(GTK_CALENDAR(d->calendar), month, year);
		gtk_calendar_select_day(GTK_CALENDAR(d->calendar), day);
		g_signal_handler_unblock(d->calendar, d->calendarBlock);
	}
	if (d->hasTime) {
		hour = g_date_time_get_hour(dt);
		if (hour >= 12) {
			hour -= 12;
			setRealSpinValue(GTK_SPIN_BUTTON(d->ampm), 1, d->ampmBlock);
		}
		setRealSpinValue(GTK_SPIN_BUTTON(d->hours), hour, d->hoursBlock);
		setRealSpinValue(GTK_SPIN_BUTTON(d->minutes), g_date_time_get_minute(dt), d->minutesBlock);
		setRealSpinValue(GTK_SPIN_BUTTON(d->seconds), g_date_time_get_seconds(dt), d->secondsBlock);
	}
	g_date_time_unref(dt);
}