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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

const char *
srate(int rate)
{
	static char buf[32];
	if (rate & 1)
		snprintf(buf, sizeof(buf), "%u.5", rate/2);
	else
		snprintf(buf, sizeof(buf), "%u", rate/2);
	return buf;
}