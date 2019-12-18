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
struct utsname {char* sysname; char* nodename; char* release; char* version; char* machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  uname (struct utsname*) ; 

void setup_hostinfo(char *buf, int len)
{
	struct utsname host;

	uname(&host);
	snprintf(buf, len, "%s %s %s %s %s", host.sysname, host.nodename,
		 host.release, host.version, host.machine);
}