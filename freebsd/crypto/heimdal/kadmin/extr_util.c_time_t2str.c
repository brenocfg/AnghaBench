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
 int /*<<< orphan*/  gmtime (scalar_t__*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*) ; 
 int /*<<< orphan*/  strftime (char*,size_t,char*,int /*<<< orphan*/ ) ; 

void
time_t2str(time_t t, char *str, size_t len, int include_time)
{
    if(t) {
	if(include_time)
	    strftime(str, len, "%Y-%m-%d %H:%M:%S UTC", gmtime(&t));
	else
	    strftime(str, len, "%Y-%m-%d", gmtime(&t));
    } else
	snprintf(str, len, "never");
}