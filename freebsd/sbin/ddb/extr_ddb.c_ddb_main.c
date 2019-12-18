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
 int /*<<< orphan*/  ddb_capture (int,char**) ; 
 int /*<<< orphan*/  ddb_script (int,char**) ; 
 int /*<<< orphan*/  ddb_scripts (int,char**) ; 
 int /*<<< orphan*/  ddb_unscript (int,char**) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 

void
ddb_main(int argc, char *argv[])
{

	if (argc < 1)
		usage();

	if (strcmp(argv[0], "capture") == 0)
		ddb_capture(argc, argv);
	else if (strcmp(argv[0], "script") == 0)
		ddb_script(argc, argv);
	else if (strcmp(argv[0], "scripts") == 0)
		ddb_scripts(argc, argv);
	else if (strcmp(argv[0], "unscript") == 0)
		ddb_unscript(argc, argv);
	else
		usage();
}