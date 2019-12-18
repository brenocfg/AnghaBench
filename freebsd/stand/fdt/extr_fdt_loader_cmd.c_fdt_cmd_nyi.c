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
 int CMD_ERROR ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
fdt_cmd_nyi(int argc, char *argv[])
{

	printf("command not yet implemented\n");
	return (CMD_ERROR);
}