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
 unsigned int INT_MAX ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*) ; 
 int /*<<< orphan*/  unparse_time (unsigned int,char*,size_t) ; 

void
deltat2str(unsigned t, char *str, size_t len)
{
    if(t == 0 || t == INT_MAX)
	snprintf(str, len, "unlimited");
    else
	unparse_time(t, str, len);
}