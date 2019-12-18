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
struct utsname {char* machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  uname (struct utsname*) ; 

void setup_machinename(char *machine_out)
{
	struct utsname host;

	uname(&host);
#ifdef UML_CONFIG_UML_X86
# ifndef UML_CONFIG_64BIT
	if (!strcmp(host.machine, "x86_64")) {
		strcpy(machine_out, "i686");
		return;
	}
# else
	if (!strcmp(host.machine, "i686")) {
		strcpy(machine_out, "x86_64");
		return;
	}
# endif
#endif
	strcpy(machine_out, host.machine);
}