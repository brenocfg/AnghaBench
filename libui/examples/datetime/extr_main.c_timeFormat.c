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

/* Variables and functions */
 int /*<<< orphan*/ * dtboth ; 
 int /*<<< orphan*/ * dtdate ; 
 int /*<<< orphan*/ * dttime ; 

const char *timeFormat(uiDateTimePicker *d)
{
	const char *fmt;

	if (d == dtboth)
		fmt = "%c";
	else if (d == dtdate)
		fmt = "%x";
	else if (d == dttime)
		fmt = "%X";
	else
		fmt = "";
	return fmt;
}