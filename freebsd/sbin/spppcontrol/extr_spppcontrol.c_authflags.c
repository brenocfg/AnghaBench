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
typedef  int u_short ;

/* Variables and functions */
 int AUTHFLAG_NOCALLOUT ; 
 int AUTHFLAG_NORECHALLENGE ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

const char *
authflags(u_short flags)
{
	static char buf[30];
	buf[0] = '\0';
	if (flags & AUTHFLAG_NOCALLOUT)
		strcat(buf, " callin");
	if (flags & AUTHFLAG_NORECHALLENGE)
		strcat(buf, " norechallenge");
	return buf;
}