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
struct TYPE_3__ {int /*<<< orphan*/  d; } ;
typedef  TYPE_1__ uiDateTimePicker ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  GDateTime ;

/* Variables and functions */
 int /*<<< orphan*/  g_date_time_to_unix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_date_time_unref (int /*<<< orphan*/ *) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct tm*,struct tm*,int) ; 
 int /*<<< orphan*/ * selected (int /*<<< orphan*/ ) ; 

void uiDateTimePickerTime(uiDateTimePicker *d, struct tm *time)
{
	time_t t;
	struct tm tmbuf;
	GDateTime *dt;

	dt = selected(d->d);
	t = g_date_time_to_unix(dt);
	g_date_time_unref(dt);

	// Copy time to minimize a race condition
	// time.h functions use global non-thread-safe data
	tmbuf = *localtime(&t);
	memcpy(time, &tmbuf, sizeof (struct tm));
}