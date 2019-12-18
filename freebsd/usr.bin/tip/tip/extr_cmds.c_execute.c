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
 int /*<<< orphan*/  SHELL ; 
 int /*<<< orphan*/  execl (char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  shell_uid () ; 
 char* strrchr (char*,char) ; 
 char* value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
execute(char *s)
{
	char *cp;

	if ((cp = strrchr(value(SHELL), '/')) == NULL)
		cp = value(SHELL);
	else
		cp++;
	shell_uid();
	execl(value(SHELL), cp, "-c", s, (char *)NULL);
}