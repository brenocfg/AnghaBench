#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v ;
struct TYPE_2__ {int /*<<< orphan*/  (* edit_cmdline ) (char*,int,unsigned int) ;} ;

/* Variables and functions */
 int BOOT_COMMAND_LINE_SIZE ; 
 char* cmdline ; 
 TYPE_1__ console_ops ; 
 int getprop (void*,char*,...) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  setprop_str (void*,char*,char*) ; 
 int /*<<< orphan*/  stub1 (char*,int,unsigned int) ; 

__attribute__((used)) static void prep_cmdline(void *chosen)
{
	unsigned int getline_timeout = 5000;
	int v;
	int n;

	/* Wait-for-input time */
	n = getprop(chosen, "linux,cmdline-timeout", &v, sizeof(v));
	if (n == sizeof(v))
		getline_timeout = v;

	if (cmdline[0] == '\0')
		getprop(chosen, "bootargs", cmdline, BOOT_COMMAND_LINE_SIZE-1);

	printf("\n\rLinux/PowerPC load: %s", cmdline);

	/* If possible, edit the command line */
	if (console_ops.edit_cmdline && getline_timeout)
		console_ops.edit_cmdline(cmdline, BOOT_COMMAND_LINE_SIZE, getline_timeout);

	printf("\n\r");

	/* Put the command line back into the devtree for the kernel */
	setprop_str(chosen, "bootargs", cmdline);
}