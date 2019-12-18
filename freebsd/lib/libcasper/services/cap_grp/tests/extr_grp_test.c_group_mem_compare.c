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
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static bool
group_mem_compare(char **mem0, char **mem1)
{
	int i0, i1;

	if (mem0 == NULL && mem1 == NULL)
		return (true);
	if (mem0 == NULL || mem1 == NULL)
		return (false);

	for (i0 = 0; mem0[i0] != NULL; i0++) {
		for (i1 = 0; mem1[i1] != NULL; i1++) {
			if (strcmp(mem0[i0], mem1[i1]) == 0)
				break;
		}
		if (mem1[i1] == NULL)
			return (false);
	}

	return (true);
}