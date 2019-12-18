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
typedef  int /*<<< orphan*/  uiDateTimePicker ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  strftime (char*,int,int /*<<< orphan*/ ,struct tm*) ; 
 int /*<<< orphan*/  timeFormat (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDateTimePickerTime (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  uiLabel (void*) ; 
 int /*<<< orphan*/  uiLabelSetText (int /*<<< orphan*/ ,char*) ; 

void onChanged(uiDateTimePicker *d, void *data)
{
	struct tm time;
	char buf[64];

	uiDateTimePickerTime(d, &time);
	strftime(buf, sizeof (buf), timeFormat(d), &time);
	uiLabelSetText(uiLabel(data), buf);
}