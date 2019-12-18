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
struct group {int /*<<< orphan*/ ** gr_mem; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static void
delete_members(struct group *grp, char *list)
{
	char *p;
	int k;

	if (grp->gr_mem == NULL)
		return;

	for (p = strtok(list, ", \t"); p != NULL; p = strtok(NULL, ", \t")) {
		for (k = 0; grp->gr_mem[k] != NULL; k++) {
			if (strcmp(grp->gr_mem[k], p) == 0)
				break;
		}
		if (grp->gr_mem[k] == NULL) /* No match */
			continue;

		for (; grp->gr_mem[k] != NULL; k++)
			grp->gr_mem[k] = grp->gr_mem[k+1];
	}
}