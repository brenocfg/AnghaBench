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
 int CMD_OK ; 
 int FDT_CWD_LEN ; 
 char* cwd ; 
 int /*<<< orphan*/  pager_close () ; 
 int /*<<< orphan*/  pager_open () ; 
 int /*<<< orphan*/  pager_output (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static int
fdt_cmd_pwd(int argc, char *argv[])
{
	char line[FDT_CWD_LEN];

	pager_open();
	sprintf(line, "%s\n", cwd);
	pager_output(line);
	pager_close();
	return (CMD_OK);
}