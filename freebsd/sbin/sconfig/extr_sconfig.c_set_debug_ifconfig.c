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
 char* chan_name ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  system (char*) ; 

__attribute__((used)) static void
set_debug_ifconfig (int on)
{
	char buf [64];
	sprintf (buf, "ifconfig %s %sdebug 2>/dev/null", chan_name,
		 on ? "" : "-");
	system (buf);
}