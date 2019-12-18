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
typedef  scalar_t__ time_t ;

/* Variables and functions */
 scalar_t__ bios_seconds () ; 

time_t
time(time_t *t)
{
    static time_t lasttime;
    time_t now, check;
    int same, try;

    same = try = 0;
    check = bios_seconds();
    do {
	now = check;
	check = bios_seconds();
	if (check != now)
	    same = 0;
    } while (++same < 8 && ++try < 1000);

    if (now < lasttime)
	now += 24 * 3600;
    lasttime = now;
    
    if (t != NULL)
	*t = now;
    return(now);
}