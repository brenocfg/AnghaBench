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

/* Variables and functions */
 int strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 

__attribute__((used)) static int
ds3231_str_sqw_mode(char *buf)
{
	int len, rtrn;

	rtrn = -1;
	len = strlen(buf);
	if ((len > 2 && strncasecmp("interrupt", buf, len) == 0) ||
	    (len > 2 && strncasecmp("int", buf, len) == 0)) {
		rtrn = 1;
	} else if ((len > 2 && strncasecmp("square-wave", buf, len) == 0) ||
	    (len > 2 && strncasecmp("sqw", buf, len) == 0)) {
		rtrn = 0;
	}

	return (rtrn);
}