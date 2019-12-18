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
struct userconf {char* default_group; } ;
struct group {int /*<<< orphan*/  gr_name; } ;

/* Variables and functions */
 struct group* group_from_name_or_id (char*) ; 
 char* newstr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
validate_grname(struct userconf *cnf, char *group)
{
	struct group *grp;

	if (group == NULL || *group == '\0') {
		cnf->default_group = "";
		return;
	}
	grp = group_from_name_or_id(group);
	cnf->default_group = newstr(grp->gr_name);
}