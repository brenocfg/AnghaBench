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
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GETS_ECHO ; 
 int /*<<< orphan*/  cngets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_dev_print () ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  parse_dir_ask_printenv (char*) ; 
 int parse_mount (char**) ; 
 int /*<<< orphan*/  pause (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  vfs_mountroot_wait () ; 

__attribute__((used)) static int
parse_dir_ask(char **conf)
{
	char name[80];
	char *mnt;
	int error;

	vfs_mountroot_wait();

	printf("\nLoader variables:\n");
	parse_dir_ask_printenv("vfs.root.mountfrom");
	parse_dir_ask_printenv("vfs.root.mountfrom.options");

	printf("\nManual root filesystem specification:\n");
	printf("  <fstype>:<device> [options]\n");
	printf("      Mount <device> using filesystem <fstype>\n");
	printf("      and with the specified (optional) option list.\n");
	printf("\n");
	printf("    eg. ufs:/dev/da0s1a\n");
	printf("        zfs:zroot/ROOT/default\n");
	printf("        cd9660:/dev/cd0 ro\n");
	printf("          (which is equivalent to: ");
	printf("mount -t cd9660 -o ro /dev/cd0 /)\n");
	printf("\n");
	printf("  ?               List valid disk boot devices\n");
	printf("  .               Yield 1 second (for background tasks)\n");
	printf("  <empty line>    Abort manual input\n");

	do {
		error = EINVAL;
		printf("\nmountroot> ");
		cngets(name, sizeof(name), GETS_ECHO);
		if (name[0] == '\0')
			break;
		if (name[0] == '?' && name[1] == '\0') {
			printf("\nList of GEOM managed disk devices:\n  ");
			g_dev_print();
			continue;
		}
		if (name[0] == '.' && name[1] == '\0') {
			pause("rmask", hz);
			continue;
		}
		mnt = name;
		error = parse_mount(&mnt);
		if (error == -1)
			printf("Invalid file system specification.\n");
	} while (error != 0);

	return (error);
}