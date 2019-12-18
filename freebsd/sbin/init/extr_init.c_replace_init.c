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
 int /*<<< orphan*/  execute_script (char**) ; 

__attribute__((used)) static void
replace_init(char *path)
{
	char *argv[3];
	char sh[] = "sh";

	argv[0] = sh;
	argv[1] = path;
	argv[2] = NULL;

	execute_script(argv);
}