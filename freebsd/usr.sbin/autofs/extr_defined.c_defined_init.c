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
struct utsname {char* machine; char* nodename; char* sysname; char* release; char* version; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  defined_add (char*,char*) ; 
 int /*<<< orphan*/  defined_values ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int uname (struct utsname*) ; 

void
defined_init(void)
{
	struct utsname name;
	int error;

	TAILQ_INIT(&defined_values);

	error = uname(&name);
	if (error != 0)
		log_err(1, "uname");

	defined_add("ARCH", name.machine);
	defined_add("CPU", name.machine);
	defined_add("DOLLAR", "$");
	defined_add("HOST", name.nodename);
	defined_add("OSNAME", name.sysname);
	defined_add("OSREL", name.release);
	defined_add("OSVERS", name.version);
}