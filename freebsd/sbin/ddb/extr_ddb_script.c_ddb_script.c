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
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  SYSCTL_SCRIPT ; 
 int /*<<< orphan*/  SYSCTL_SCRIPTS ; 
 int /*<<< orphan*/  ddb_list_scripts (char*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strchr (char*,char) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ sysctlbyname (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  usage () ; 

void
ddb_script(int argc, char *argv[])
{

	if (argc != 2)
		usage();
	argv++;
	argc--;
	if (strchr(argv[0], '=') != 0) {
		if (sysctlbyname(SYSCTL_SCRIPT, NULL, NULL, argv[0],
		    strlen(argv[0]) + 1) < 0)
			err(EX_OSERR, "sysctl: %s", SYSCTL_SCRIPTS);
	} else
		ddb_list_scripts(argv[0]);
}