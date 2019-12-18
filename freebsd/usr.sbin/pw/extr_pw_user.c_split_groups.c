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
struct group {int /*<<< orphan*/  gr_name; } ;
typedef  int /*<<< orphan*/  StringList ;

/* Variables and functions */
 struct group* group_from_name_or_id (char*) ; 
 int /*<<< orphan*/  newstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sl_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sl_init () ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static void
split_groups(StringList **groups, char *groupsstr)
{
	struct group *grp;
	char *p;
	char tok[] = ", \t";

	if (*groups == NULL)
		*groups = sl_init();
	for (p = strtok(groupsstr, tok); p != NULL; p = strtok(NULL, tok)) {
		grp = group_from_name_or_id(p);
		sl_add(*groups, newstr(grp->gr_name));
	}
}