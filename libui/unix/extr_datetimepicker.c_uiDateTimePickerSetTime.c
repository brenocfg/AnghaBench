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
struct TYPE_3__ {int /*<<< orphan*/  setBlock; int /*<<< orphan*/  d; } ;
typedef  TYPE_1__ uiDateTimePicker ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dateTimeChanged (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_date_time_new_from_unix_local (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_handler_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_handler_unblock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct tm*,struct tm const*,int) ; 
 int /*<<< orphan*/  mktime (struct tm*) ; 
 int /*<<< orphan*/  uiprivDateTimePickerWidget_setTime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void uiDateTimePickerSetTime(uiDateTimePicker *d, const struct tm *time)
{
	time_t t;
	struct tm tmbuf;

	// TODO find a better way to avoid this; possibly by removing the signal entirely, or the call to dateTimeChanged() (most likely both)
	g_signal_handler_block(d->d, d->setBlock);

	// Copy time because mktime() modifies its argument
	memcpy(&tmbuf, time, sizeof (struct tm));
	t = mktime(&tmbuf);

	uiprivDateTimePickerWidget_setTime(d->d, g_date_time_new_from_unix_local(t));
	dateTimeChanged(d->d);

	g_signal_handler_unblock(d->d, d->setBlock);
}