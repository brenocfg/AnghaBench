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
struct varlist {char* name; char* value; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t MAXLIST ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
doprintvlist(
	struct varlist *vlist,
	FILE *fp
	)
{
	size_t n;

	if (NULL == vlist->name) {
		fprintf(fp, "No variables on list\n");
		return;
	}
	for (n = 0; n < MAXLIST && vlist[n].name != NULL; n++) {
		if (NULL == vlist[n].value)
			fprintf(fp, "%s\n", vlist[n].name);
		else
			fprintf(fp, "%s=%s\n", vlist[n].name,
				vlist[n].value);
	}
}