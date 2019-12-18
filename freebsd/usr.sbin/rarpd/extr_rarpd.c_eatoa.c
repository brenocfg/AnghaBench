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
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int,int,int) ; 

__attribute__((used)) static char *
eatoa(u_char *ea)
{
	static char buf[sizeof("xx:xx:xx:xx:xx:xx")];

	(void)sprintf(buf, "%x:%x:%x:%x:%x:%x",
	    ea[0], ea[1], ea[2], ea[3], ea[4], ea[5]);
	return (buf);
}