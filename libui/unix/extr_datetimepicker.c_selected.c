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
struct TYPE_3__ {int /*<<< orphan*/  seconds; int /*<<< orphan*/  minutes; int /*<<< orphan*/  ampm; int /*<<< orphan*/  hours; scalar_t__ hasTime; int /*<<< orphan*/  calendar; scalar_t__ hasDate; } ;
typedef  TYPE_1__ uiprivDateTimePickerWidget ;
typedef  int guint ;
typedef  int /*<<< orphan*/  GDateTime ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_CALENDAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_SPIN_BUTTON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_date_time_new_local (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  gtk_calendar_get_date (int /*<<< orphan*/ ,int*,int*,int*) ; 
 scalar_t__ realSpinValue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static GDateTime *selected(uiprivDateTimePickerWidget *d)
{
	// choose a day for which all times are likely to be valid for the default date in case we're only dealing with time
	guint year = 1970, month = 1, day = 1;
	guint hour = 0, minute = 0, second = 0;

	if (d->hasDate) {
		gtk_calendar_get_date(GTK_CALENDAR(d->calendar), &year, &month, &day);
		month++;		// GtkCalendar/GDateTime differences
	}
	if (d->hasTime) {
		hour = realSpinValue(GTK_SPIN_BUTTON(d->hours));
		if (realSpinValue(GTK_SPIN_BUTTON(d->ampm)) != 0)
			hour += 12;
		minute = realSpinValue(GTK_SPIN_BUTTON(d->minutes));
		second = realSpinValue(GTK_SPIN_BUTTON(d->seconds));
	}
	return g_date_time_new_local(year, month, day, hour, minute, second);
}