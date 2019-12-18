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
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

void usage(char *name)
{
	printf("Usage: %s <opts>\n"
	       "-h\thelp\n"
	       "-i\t<iface>\n"
	       "-s\t<ssid>\n"
	       "-m\t<mac>\n"
	       "-w\t<wep key>\n"
	       "-c\t<chan>\n"
	       "-t\t<tap>\n"
	       , name);
	exit(0);
}