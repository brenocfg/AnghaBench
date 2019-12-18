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
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static bool
_res_checkenv(char *envp)
{
	char *cp;

	cp = envp;
	while (cp) {
		if (strncmp(cp, "hint.", 5) == 0)
			return (true);
		while (*cp != '\0')
			cp++;
		cp++;
		if (*cp == '\0')
			break;
	}
	return (false);
}