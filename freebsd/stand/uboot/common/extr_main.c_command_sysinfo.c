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
struct sys_info {int dummy; } ;

/* Variables and functions */
 int CMD_ERROR ; 
 int CMD_OK ; 
 char* command_errmsg ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  ub_dump_si (struct sys_info*) ; 
 struct sys_info* ub_get_sys_info () ; 

__attribute__((used)) static int
command_sysinfo(int argc, char *argv[])
{
	struct sys_info *si;

	if ((si = ub_get_sys_info()) == NULL) {
		command_errmsg = "could not retrieve U-Boot sys info!?";
		return (CMD_ERROR);
	}

	printf("U-Boot system info:\n");
	ub_dump_si(si);
	return (CMD_OK);
}