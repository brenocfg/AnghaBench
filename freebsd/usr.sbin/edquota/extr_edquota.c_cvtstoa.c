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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ,char*) ; 

char *
cvtstoa(uint64_t secs)
{
	static char buf[20];

	if (secs % (24 * 60 * 60) == 0) {
		secs /= 24 * 60 * 60;
		sprintf(buf, "%ju day%s", (uintmax_t)secs,
		    secs == 1 ? "" : "s");
	} else if (secs % (60 * 60) == 0) {
		secs /= 60 * 60;
		sprintf(buf, "%ju hour%s", (uintmax_t)secs,
		    secs == 1 ? "" : "s");
	} else if (secs % 60 == 0) {
		secs /= 60;
		sprintf(buf, "%ju minute%s", (uintmax_t)secs,
		    secs == 1 ? "" : "s");
	} else
		sprintf(buf, "%ju second%s", (uintmax_t)secs,
		    secs == 1 ? "" : "s");
	return (buf);
}